#include <stdio.h>
#include <math.h>

#define L 20
#define V L*L
#define MAX_ITER 100

#define RIGHT 0
#define TOP 1
#define LEFT 2
#define BOTTOM 3

typedef unsigned long long RANDOM_TYPE;
typedef char SPIN;

#define MYRAND64  myRand64 = (6364136223846793005ULL * myRand64)
#define MAX_RAND64     0XFFFFFFFFFFFFFFFFULL
RANDOM_TYPE myRand64;
double inverseMaxRand64 = 1.0 / (double)MAX_RAND64;

unsigned long neighbor[V][4];

struct siteCluster{
  SPIN spin;
  unsigned int label;
} cluster[V];

void myInit(void);
void initNeighbors(void);
void initRandomSpin(void);
unsigned long siteUpdate(long, long);
void myEnd(void);

#define FAILURE -1
#define SUCCESS 1

/*****************************************************************************/
int main(void)
{
  long i, j;
  unsigned long somethingChanged;

  myInit();
  initNeighbors();
  initRandomSpin();
  j = 0;
  somethingChanged = 0;
  while( (j < MAX_ITER) && (somethingChanged != 0)){
    j++;
    somethingChanged = 0;
    for(i = 0; i < V; i++){
      somethingChanged += 
	(unsigned long) siteUpdate((long)RIGHT, i);
      somethingChanged += 
	(unsigned long) siteUpdate((long)BOTTOM, i);
      somethingChanged += 
	(unsigned long) siteUpdate((long)LEFT, i);
      somethingChanged += 
	(unsigned long) siteUpdate((long)TOP, i);
    }
    printf("# numero cambiamenti %ld\n", somethingChanged);
  }
  myEnd();
  if(somethingChanged > 0){
    printf("Non siamo riusciti a costruire il cluster\n");
    return FAILURE;
  } else {
    return SUCCESS;
  }
}

/*****************************************************************************/
void myEnd(void)
{

  long i, j;

  for(j = 0; j < L; j++){printf("-----------");}
  printf("-\n");
  for(i = 0; i < L; i++){
    for(j = 0; j < L; j++){
      printf("| %2d (%4d) ",
	     cluster[j + i * L].spin, 
	     cluster[j + i * L].label);
    }
    printf("|\n");
    for(j = 0; j < L; j++){printf("-----------");}
    printf("-\n");
  }
  printf("\n");
}

/*****************************************************************************/
unsigned long siteUpdate(long direction, long site)
{
  long i, j; 
  unsigned long weAreChanging = 0;
  
  unsigned long int n = neighbor[site][direction];
  if(cluster[site].spin == 
     cluster[n].spin){
    if(cluster[site].label < cluster[n].label){
      weAreChanging = 1;
      cluster[n].label = cluster[site].label;
    }
    else if(cluster[site].label > cluster[n].label){
      weAreChanging = 1;
      cluster[site].label = cluster[n].label ;
    }
  }
  return weAreChanging;
}

/****************************************************************************/
void initNeighbors(void)
{
  long x, y, i;

  for(x = 0; x < L; x++){
    long xp, xm;
    xp = x + 1; 
    if(x == L - 1) xp = 0;
    xm = x - 1; 
    if(x == 0) xm = L - 1;
    for(y = 0; y < L; y++){
      long yp, ym;
      yp = y + 1; 
      if(y == L - 1) yp = 0;
      ym = y - 1; 
      if(y == 0) ym = L - 1;
      neighbor[x + L * y][RIGHT]  = xp + L *  y;
      neighbor[x + L * y][TOP]    =  x + L * yp;
      neighbor[x + L * y][LEFT]   = xm + L *  y;
      neighbor[x + L * y][BOTTOM] =  x + L * ym;
    }
  }
}

/*****************************************************************************/
void initRandomSpin(void)
{
  long i, j;

  for(i = 0; i < V; i++){
    MYRAND64;
    if((double)myRand64 * inverseMaxRand64 < 0.5){
      cluster[i].spin = -1;
    }
    else{
      cluster[i].spin = 1;
    }
  }

  for(i = 0; i < L; i++){
    for(j = 0; j < L; j++){
      cluster[j + i * L].label   = j + i * L;
    }
  }

  /*
  for(j = 0; j < L; j++){
    printf("-----");
  }
  printf("-\n");
  for(i = 0; i < L; i++){
    for(j = 0; j < L; j++){
      printf("| %2d ",cluster[j+i*L].spin);
    }
    printf("|\n");
    for(j = 0; j < L; j++){
      printf("-----");
    }
    printf("-\n");
  }
  printf("\n");
  */
}

/*****************************************************************************/
void myInit(void)
{

  int randomSeed;
  long i;

  printf("# L = %d\n", L);
  printf("# Please input random seed _ \n"); 
  fflush(stdout);
  scanf("%d", &randomSeed);
  printf("# randomSeed = %d\n", randomSeed); 
  fflush(stdout);

  myRand64 = (RANDOM_TYPE)randomSeed;
  for(i = 0; i < 1000; i++){MYRAND64;}
}
