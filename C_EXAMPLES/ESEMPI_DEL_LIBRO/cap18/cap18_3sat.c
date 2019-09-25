/*
  cap18_3sat.c: A program for studying the random 3-sat problem.
  Copyright (C) 2006 Federico Ricci-Tersenghi (Federico.Ricci@roma1.infn.it)

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

  This program has been extracted from "Programmazione Scientifica",
  Pearson Education ed. (2006), by Barone, Marinari, Organtini and
  Ricci-Tersenghi. ISBN 8871922425.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FNORM   (2.3283064365e-10)
#define RANDOM  ( (ira[ip++]=ira[ip1++]+ira[ip2++]) ^ira[ip3++] )        
#define FRANDOM (FNORM * RANDOM)
#define pm1 ((FRANDOM > 0.5) ? 1 : -1)

#define N 20
#define M_MIN 60
#define M_STEP 1
#define M_MAX 100

/* Variabili che si fissano al momento della creazione della formula globale */
unsigned glob_literal[3*M_MAX], max_rep;
int glob_sign[3*M_MAX];

/* Variabili che si fissano al momento della creazione della subformula */
unsigned M, literal[3*M_MAX], *clause_with, num_clauses_with[N];
int sign[3*M_MAX];

/* Variabili dinamiche */
int assign[N], bb_assign[N];
unsigned bb[N], bb_size, num_sol, num_calls, num_calls_1;

/* Variabili riguardanti il generatore random */
unsigned myrand, ira[256];
unsigned char ip,ip1,ip2,ip3;

unsigned rand4init(void)
{
  unsigned long long y;
  
  y = (myrand*16807LL);
  myrand = (y&0x7fffffff) + (y>>31);	  	  	                  
  if (myrand&0x80000000)
    myrand = (myrand&0x7fffffff) + 1;
  return myrand;
}

void Init_Random(void)
{
  unsigned i;
  
  ip=128;
  ip1=ip-24;
  ip2=ip-55;
  ip3=ip-61;
  
  for (i=ip3; i<ip; i++)
    ira[i] = rand4init();
}

void Init_Global_Formula(void)
{
  unsigned i, lit1, lit2, lit3;
  
  for (i=0; i<N; i++)
    num_clauses_with[i] = 0;

  for (i=0; i<M_MAX; i++) {

    lit1 = (unsigned)(FRANDOM*N);
    do
      lit2 = (unsigned)(FRANDOM*N);
    while (lit2 == lit1);
    do
      lit3 = (unsigned)(FRANDOM*N);
    while (lit3 == lit1 || lit3 == lit2);

    glob_literal[3*i] = lit1;
    glob_literal[3*i+1] = lit2;
    glob_literal[3*i+2] = lit3;

    glob_sign[3*i] = pm1;
    glob_sign[3*i+1] = pm1;
    glob_sign[3*i+2] = pm1;

    num_clauses_with[lit1]++;
    num_clauses_with[lit2]++;
    num_clauses_with[lit3]++;
  }

  max_rep = 0;
  for (i=0; i<N; i++)
    if (num_clauses_with[i] > max_rep)
      max_rep = num_clauses_with[i];

  clause_with = (unsigned*)calloc(N*max_rep, sizeof(unsigned));
}

void Create_Subformula(void)
{
  unsigned i;

  for (i=0; i<N; i++)
    num_clauses_with[i] = 0;
 
  for (i=0; i<3*M; i++) {
    literal[i] = glob_literal[i];
    sign[i] = glob_sign[i];
    clause_with[literal[i] * max_rep + num_clauses_with[literal[i]]] =
      3 * (unsigned)(i/3);
    num_clauses_with[literal[i]]++;
  }
}

void Assign(unsigned lit)
{
  unsigned i, offset, flag;
  
  num_calls++;
  if (num_sol == 0)
    num_calls_1++;
  
  assign[lit] = 1;
  flag = 1;
  for (i=0; i<num_clauses_with[lit] && flag; i++) {
    offset = clause_with[lit*max_rep+i];
    if (assign[literal[offset]] *
	assign[literal[offset+1]] *
	assign[literal[offset+2]])
      if (assign[literal[offset]] * sign[offset] +
	  assign[literal[offset+1]] * sign[offset+1] +
	  assign[literal[offset+2]] * sign[offset+2] == -3)
	flag = 0;
  }
  if (flag) {
    if (lit+1 < N)
      Assign(lit+1);
    else {
      num_sol++;
      if (num_sol == 1) {
	for (i=0; i<N; i++) {
	  bb_assign[i] = assign[i];
	  bb[i] = 1;
	}
	bb_size = N;
      } else
	for (i=0; i<N; i++)
	  if (bb[i] && (assign[i] != bb_assign[i])) {
	    bb[i] = 0;
	    bb_size--;
	  }
    }
  }

  assign[lit] = -1;
  flag = 1;
  for (i=0; i<num_clauses_with[lit] && flag; i++) {
    offset = clause_with[lit*max_rep+i];
    if (assign[literal[offset]] *
	assign[literal[offset+1]] *
	assign[literal[offset+2]])
      if (assign[literal[offset]] * sign[offset] +
	  assign[literal[offset+1]] * sign[offset+1] +
	  assign[literal[offset+2]] * sign[offset+2] == -3)
	flag = 0;
  }
  if (flag) {
    if (lit+1 < N)
      Assign(lit+1);
    else {
      num_sol++;
      if (num_sol == 1) {
	for (i=0; i<N; i++) {
	  bb_assign[i] = assign[i];
	  bb[i] = 1;
	}
	bb_size = N;
      } else
	for (i=0; i<N; i++)
	  if (bb[i] && (assign[i] != bb_assign[i])) {
	    bb[i] = 0;
	    bb_size--;
	  }
    }
  }

  assign[lit] = 0;
}

void main(int argc, char *argv[])
{
  unsigned i, is, n_samples;

  if (argc != 3) {
    fprintf(stderr, "usage: %s <n_samples> <seed>\n", argv[0]);
    exit(1);
  }
  
  n_samples = (unsigned)atoi(argv[1]);
  myrand = (unsigned)atoi(argv[2]);

  printf("# N = %d   M = %d -> %d   n_samples = %d   random_seed = %u\n",
	 N, M_MIN, M_MAX, n_samples, myrand);
  printf("# N M num_sol bb_size num_calls num_calls_1\n");
  fflush(stdout);
  
  Init_Random();

  for (is=0; is<n_samples; is++) {

    Init_Global_Formula();
    
    for (M=M_MIN; M<=M_MAX; M+=M_STEP) {
      
      Create_Subformula();

      num_sol = 0;
      bb_size = 0;
      num_calls = 0;
      num_calls_1 = 0;
      for (i=0; i<N; i++)
	assign[i] = 0;
      Assign(0);
      
      printf("%d %d %d %d %d %d\n",
	     N, M, num_sol, bb_size, num_calls, num_calls_1);
    }
/*     printf("\n"); */
    free(clause_with);
  }
}
