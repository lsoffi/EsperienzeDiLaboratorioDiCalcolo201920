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
  struct siteCluster *next;
  struct siteCluster *former;
  struct siteCluster *parent;
  struct siteCluster *son;
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
      somethingChanged += (unsigned long) siteUpdate((long)RIGHT, i);
      somethingChanged += (unsigned long) siteUpdate((long)BOTTOM, i);
      somethingChanged += (unsigned long) siteUpdate((long)LEFT, i);
      somethingChanged += (unsigned long) siteUpdate((long)TOP, i);
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
	     cluster[j + i * L].parent-cluster);
    }
    printf("|\n");
    for(j = 0; j < L; j++){printf("-----------");}
    printf("-\n");
  }
  printf("\n");

  /*
  printf(" ENDALL");
  for(i = 0; i < L; i++){
    for(j = 0; j < L; j++){
      printf(" | + %d - %d A %d Z %d",
	     cluster[j + i * L].next    - cluster,
	     cluster[j + i * L].former  - cluster,
	     cluster[j + i * L].parent  - cluster,
	     cluster[j + i * L].son     - cluster);
    }
    if(i < L - 1)printf("|\n ENDALL");
  }
  printf("\n");
  */
}

/*****************************************************************************/
unsigned long siteUpdate(long direction, long site)
{
  long i, j; 
  unsigned long weAreChanging = 0UL;
  long lowerSite, upperSite;
  struct siteCluster *upperHead, *upperTail;
  struct siteCluster *lowerHead, *lowerTail;
  struct siteCluster *scratchSiteCluster;
  
  unsigned long int n = neighbor[site][direction];
  if((cluster[site].spin == cluster[n].spin) &&
     (cluster[site].parent != cluster[n].parent)){
    
    /* qui si cambia */
    weAreChanging = 1UL;
    
    /* copieremo dal site con parent piu' piccolo
       a quello con parent piu' grande */
    if(cluster[site].parent < cluster[n].parent){
      lowerSite = site;
      upperSite = n;
    } else {
      lowerSite =  n;
      upperSite = site;
    }

    /* siccome dovremo cambiare i valori conserviamo
       i dati che ci serviranno, come head e tail dei 
       due cluster che stiamo fondendo */
    upperHead = cluster[upperSite].parent;
    upperTail = cluster[upperSite].son;
    lowerHead = cluster[lowerSite].parent;
    lowerTail = cluster[lowerSite].son;

    /* il parent del lower cluster viene dato a tutti i siti 
       dell'upper cluster */   
    scratchSiteCluster = upperHead; 
    scratchSiteCluster->parent = lowerHead;
    while(scratchSiteCluster != scratchSiteCluster->next){
      scratchSiteCluster = scratchSiteCluster->next;
      scratchSiteCluster->parent = lowerHead;
    } 
    
    /* il son dell'upper cluster viene dato a tutti i siti 
       del lower cluster */
    scratchSiteCluster = lowerHead;
    scratchSiteCluster->son = upperTail;
    while(scratchSiteCluster != scratchSiteCluster->next){
      scratchSiteCluster = scratchSiteCluster->next;
      scratchSiteCluster->son = upperTail;
    } 

    if(lowerTail->next != lowerTail){
      printf("interruzione programma: errore interno 1\n");
      exit(-9);
    }
    lowerTail->next = upperHead;
    if(upperHead->former != upperHead){
      printf("interruzione programma: errore interno 2\n");
      exit(-9);
    }
    upperHead->former = lowerTail;
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
      cluster[j + i * L].next   = cluster + (j + i * L);
      cluster[j + i * L].former = cluster + (j + i * L);
      cluster[j + i * L].parent = cluster + (j + i * L);
      cluster[j + i * L].son    = cluster + (j + i * L);
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

  /*
  printf(" STAALL");
  for(i = 0; i < L; i++){
    for(j = 0; j < L; j++){
      printf(" | + %d - %d A %d Z %d",
	     cluster[j+i*L].next-cluster,
	     cluster[j+i*L].former-cluster,
	     cluster[j+i*L].parent-cluster,
	     cluster[j+i*L].son-cluster);
    }
    if(i < L-1) printf("|\n STAALL");
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
