
union myConversion {
  float myfloat;
  int myInt;  
};

main() {
  int i;
  union myConversion conversion;

  printf("Input:\n");
  scanf("%g", &(conversion.myfloat) );
  printf("Il numero float vale %g\n", conversion.myfloat);
  for(i = 0; i < 32; i++) {
    printf("bit %u = %u\n", i, (1 & (conversion.myInt >> i) ) );
  }
}
