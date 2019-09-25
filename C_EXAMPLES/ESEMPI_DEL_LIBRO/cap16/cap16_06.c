/*
  cap16_binaryTreeDepth.c: Measuring the depth of a binary search tree.
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
#define RANDOM  ((ira[ip++] = ira[ip1++] + ira[ip2++]) ^ ira[ip3++])
#define FRANDOM (FNORM * RANDOM)
#define pm1 ((FRANDOM > 0.5) ? 1 : -1)

typedef float dataType;

struct node {
  dataType datum;
  struct node *up, *left, *right;
};

typedef struct node myNode;

/* variabili globali per il generatore random */
unsigned myrand, ira[256];
unsigned char ip, ip1, ip2, ip3;

unsigned randForInit(void);
void initRandom(void);
float gaussRan(void);
void error(char *);
void insertNode(myNode *, myNode *);
int nodeDepth(myNode *);
myNode *deleteNode(myNode *, myNode **);
myNode *removeNodeMax1Child(myNode *, myNode **);
myNode *searchItem(dataType, myNode *);
myNode *minimumInTree(myNode *);
myNode *maximumInTree(myNode *);
myNode *nextItem(myNode *);
myNode *previousItem(myNode *);

int main(int argc, char *argv[]) {
  int numNodes, numTrees, i, j, numLeafs, *leafsOfDepth;
  myNode *n, *root, *wn;
  double *aveLeafsOfDepth;

  if (argc != 4) {
    fprintf(stderr, "usage: %s <numNodes> <numTrees> <seed>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  numNodes = atoi(argv[1]);
  numTrees = atoi(argv[2]);
  myrand = (unsigned)atoi(argv[3]);
  if (myrand == 2147483647)
    error("seed must be less than 2147483647");
  initRandom();
  n = (myNode *)calloc(numNodes, sizeof(myNode));
  leafsOfDepth = (int *)calloc(numNodes + 1, sizeof(int));
  aveLeafsOfDepth = (double *)calloc(numNodes + 1, sizeof(double));
  printf("# numNodes = %i   numTrees = %i\n", numNodes, numTrees);
  printf("# depth aveLeafsOfDepth\n");
  for (j = 0; j < numTrees; j++) {
    root = n;
    root->datum = FRANDOM;
    root->up = NULL;
    root->left = NULL;
    root->right = NULL;
    for (i = 1, wn = n + 1; i < numNodes; i++, wn++) {
      wn->datum = FRANDOM;
      wn->up = NULL;
      wn->left = NULL;
      wn->right = NULL;
      insertNode(wn, root);
    }
    numLeafs = 0;
    for (i = 0; i <= numNodes; i++) {
      leafsOfDepth[i] = 0;
    }
    for (wn = n; wn < n + numNodes; wn++) {
      if (wn->left == NULL && wn->right == NULL) {
	numLeafs++;
	leafsOfDepth[nodeDepth(wn)]++;
      }
    }
    for (i = 0; i <= numNodes; i++) {
      aveLeafsOfDepth[i] += (double)leafsOfDepth[i] / numLeafs;
    }
  }
  for (i = 0; i <= numNodes; i++) {
    if (aveLeafsOfDepth[i]) {
      printf("%i %g\n", i, aveLeafsOfDepth[i] / numTrees);
    }
  }
  return 0;
}

void insertNode(myNode *new, myNode *old) {
  if (new->datum <= old->datum) {
    if (old->left == NULL) {
      old->left = new;
      new->up = old;
    } else {
      insertNode(new, old->left);
    }
  } else {      
    if (old->right == NULL) {
      old->right = new;
      new->up = old;
    } else {
      insertNode(new, old->right);
    }
  }
}

myNode *deleteNode(myNode *pNode, myNode **pRoot) {
  myNode *pNext;

  if (pNode->left == NULL || pNode->right == NULL) {
    return removeNodeMax1Child(pNode, pRoot);
  } else {
    pNext = nextItem(pNode);
    pNode->datum = pNext->datum;
    return removeNodeMax1Child(pNext, pRoot);
  }
}

myNode *removeNodeMax1Child(myNode *pNode, myNode **pRoot) {
  myNode *pChild;
  
  if (pNode->left != NULL) {
    pChild = pNode->left;
  } else {
    pChild = pNode->right;
  }
  if (pChild != NULL) {
    pChild->up = pNode->up;
  }
  if (pNode == *pRoot) {
    *pRoot = pChild;
  } else if (pNode->up->left == pNode) {
    pNode->up->left = pChild;
  } else {
    pNode->up->right = pChild;
  }
  return pNode;
}

int nodeDepth(myNode *pNode) {
  int depth = 0;
  
  while (pNode->up != NULL) {
    pNode = pNode->up;
    depth++;
  }
  return depth;
}

myNode *searchItem(dataType item, myNode *pNode) {
  if (pNode == NULL || item == pNode->datum) {
    return pNode;
  } else if (item < pNode->datum) {
    return searchItem(item, pNode->left);
  } else {
    return searchItem(item, pNode->right);
  }
}

myNode *minimumInTree(myNode *pNode) {
  while (pNode->left != NULL) {
    pNode = pNode->left;
  }
  return pNode;
}

myNode *maximumInTree(myNode *pNode) {
  while (pNode->right != NULL) {
    pNode = pNode->right;
  }
  return pNode;
}

myNode *nextItem(myNode *pNode) {
  myNode *pParent = pNode->up;
  if (pNode->right != NULL) {
    return minimumInTree(pNode->right);
  }
  while (pParent != NULL && pNode == pParent->right) {
    pNode = pParent;
    pParent = pNode->up;
  }
  return pParent;
}

myNode *previousItem(myNode *pNode) {
  myNode *pParent = pNode->up;
  if (pNode->left != NULL) {
    return maximumInTree(pNode->left);
  }
  while (pParent != NULL && pNode == pParent->left) {
    pNode = pParent;
    pParent = pNode->up;
  }
  return pParent;
}

unsigned randForInit(void) {
  unsigned long long y;
  
  y = myrand * 16807LL;
  myrand = (y & 0x7fffffff) + (y >> 31);
  if (myrand & 0x80000000) {
    myrand = (myrand & 0x7fffffff) + 1;
  }
  return myrand;
}

void initRandom(void) {
  int i;
  
  ip = 128;    
  ip1 = ip - 24;    
  ip2 = ip - 55;    
  ip3 = ip - 61;
  
  for (i = ip3; i < ip; i++) {
    ira[i] = randForInit();
  }
}

float gaussRan(void) {
  static int iset = 0;
  static float gset;
  float fac, rsq, v1, v2;

  if (iset == 0) {
    do {
      v1 = 2.0 * FRANDOM - 1.0;
      v2 = 2.0 * FRANDOM - 1.0;
      rsq = v1 * v1 + v2 * v2;
    } while (rsq >= 1.0 || rsq == 0.0);
    fac = sqrt(-2.0 * log(rsq) / rsq);
    gset = v1 * fac;
    iset = 1;
    return v2 * fac;
  } else {
    iset = 0;
    return gset;
  }
}

void error(char *string) {
  fprintf(stderr, "ERROR: %s\n", string);
  exit(EXIT_FAILURE);
}
