#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main(int argc, char **argv)
{
  printf("8+7=%d 3.2+8.4=%G 2^2+4^2=%G sqrt(36)=%.7G\n", 8+7, 3.2+8.4, pow(2,2)+pow(4,2), sqrt(36));
  printf("cos(pi/6)=%.7G sin(pi/6)=%.7G tanh(1)=%.7G sinh(0)=%.7G\n", cos(M_PI/6), sin(M_PI/6), tanh(1), sinh(0));
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
  printf("cos(pi/6)+10=%.7F cos(pi/6)+10=%.7G \n", cos(M_PI/6)+10., cos(M_PI/6)+10.);
  return 0;// dice al sistema operativo che non ci sono errori
}

