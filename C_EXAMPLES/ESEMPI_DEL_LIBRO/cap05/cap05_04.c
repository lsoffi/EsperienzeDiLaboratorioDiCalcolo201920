#define ROW1 5
#define COL1 7
#define ROW2 COL1
#define COL2 4
main() {  
  int a[ROW1][COL1], b[ROW2][COL2], c[ROW1][COL2];
  int i, j, k;
  
  printf("\n Inserisci i coefficienti della matrice a\n");
  for (i = 0; i < ROW1; i++) {
    for (j = 0; j < COL1; j++) {
      printf("a[%d, %d] = ", i, j);
      scanf("%lf", &a[i][j]);
    }
  }
  printf("\n Inserisci i coefficienti della matrice b\n");
  for (i = 0; i < ROW2; i++) {
    for (j = 0; j < COL2; j++) {
      printf("b[%d, %d] = ", i, j);
      scanf("%lf", &b[i][j]);
    }
  }  
  for (i = 0; i < ROW1; i++) {
     for (j = 0; j < COL2; j++) {
	c[i][j] = 0;
	for (k = 0; k < COL1; k++) {
           c[i][j] += a[i][k] * b[k][j];
	}
     }
  }
  printf("\n Stampa della matrice prodotto c\n");  
  for (i = 0; i < ROW1; i++) {
    for (j = 0; j < COL2; j++) {
      printf("c[%d, %d] = %d", i, j, c[i][j]);
    }
  }  
}
