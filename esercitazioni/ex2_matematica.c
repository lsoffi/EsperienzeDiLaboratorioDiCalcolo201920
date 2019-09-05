#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main(int argc, char **argv)
{
  printf("Benvenuto! Questo è un programma dimostrativo delle funzioni della libreria math.h.\n");
  printf("\n8+7=%3d [%%3d]\t\t3.2+8.4=%.4f [%%.4f]\t2^2+4^2=%.4f [%%.4f]\tsqrt(36)=%.4f [%%.4f]\n", 8+7, 3.2+8.4, pow(2,2)+pow(4,2), sqrt(36));
  printf("\ncos(pi/6)=%.4f[%%.4f]\tsin(pi/6)=%.4f[%%.4f]\ttanh(1)=%.4f [%%.4f]\tsinh(0)=%.4f [%%.4f]\n", cos(M_PI/6), sin(M_PI/6), tanh(1), sinh(0));
  /* la precision con F indica il numero di cifre dopo la virgola con G il massimo numero di cifre signficative
   * dal comando:
   *
   * > man 3 printf 
   *
   * The double argument is converted in style f or e (or F or E for G conversions).  The precision 
   * specifies the number of significant digits.  If the precision is missing, 6 digits are
   * given; if the precision is zero, it is treated as 1.  Style e is used if the exponent from
   * its conversion is less than -4 or greater than or equal to the precision.  Trailing zeros
   * are removed from the fractional part of the result; a decimal point appears only if it is
   * followed by at least one digit.
   */
  printf("\ncos(pi/6)+10=%.7F [%%.7F]\t\t\tcos(pi/6)+10=%.7G [%%.7G]\n", cos(M_PI/6)+10., cos(M_PI/6)+10.);
  printf("\ncos(pi/6)*10^8=%.7G [%%.7G]\t\tcos(pi/6)/10^3=%.7G [%%.7G]\n",cos(M_PI/6)*100000000,cos(M_PI/6.0)/10000);
  return 0;// dice al sistema operativo che non ci sono errori
}

