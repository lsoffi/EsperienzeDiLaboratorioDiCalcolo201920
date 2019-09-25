/* Questa funzione chiama la funzione bubblesort
   che si trova nel listato cap07_Bubblesort.c   */
void sortByParity(int data[], int odd[], int even[], int n) {
  int *pd;
  bubblesort(data, n);
  for (pd = data; pd < data + n; pd++) {
    if (*pd % 2) {
      *odd++ = *pd;
    } else {
      *even++ = *pd;
    }
  }
} 
