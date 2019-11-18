#include <stdio.h>
#include <math.h>
int main()
{
  int num, year;
  char day[10];
  char month[10];
  int n,opt;
  float l,N, P, S,r,R;
  //****************** punto 1.4 *****************//
  /*  printf("Che numero del mese e' oggi?\n");
  scanf("%d",&num);
  printf("Che giorno e' oggi?\n");
  scanf("%s",day);
  printf("Che mese e'?\n");
  scanf("%s",month);
  printf("Che anno e'?\n");
  scanf("%d",&year);
  printf("Oggi e' %s, %d %s %d\n", day, num, month, year);
  */
  //**************** punto 1.5 *******************//
  do{
    //  printf("Inserire il numero di lati del poligono: \n");
    scanf("%d", &n);
  }while((n<3) || (n>10));
 
  // printf("Inserire il valore del lato in cm \n");
  scanf("%f", &l);

  //**************** punto 1.6-1.7 *******************//
  N = 1/(2*tan(3.14/n));
  r = l*N;
  P = n*l;
  S = P*r/2;
  R = sqrt(r*r +l*l/4);
  /*
  printf("Inserisci 1 se vuoi N, 2 se vuoi r, 3 se vuoi P, 4 se vuoi S, 5 se vuoi R \n");
  scanf("%d", &opt);
  if(opt==1){
    printf(" N = %f\n",N);
  }else if(opt==2){
    printf(" r = %f\n",r);
  }else if(opt==3){
    printf(" P = %f\n",P);
  }else if(opt==4){
    printf(" S = %f\n",S);
  }else if(opt==5){
    printf(" R = %f\n",R);
  }
  */
  //**************** punto 1.8 *******************//
  for(int n =3; n<=10; n++){
  N = 1/(2*tan(3.14/n));
  r = l*N;
  P = n*l;
  S = P*r/2;
  R = sqrt(r*r +l*l/4);
  //printf(" N = %f, r = %f, P =%f, S=%f,R=%f \n", N,r,P,S,R);
  printf("%d %f %f %f %f %f \n", n, N,r,P,S,R);
}
  return 0;
}

