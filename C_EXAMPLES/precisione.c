#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<float.h>
#include<curses.h>
#define flt(x) ((float) x) 
#include <termios.h>

void init_press_key()
{
  struct termios info;
  tcgetattr(0, &info);          /* get current terminal attirbutes; 0 is the file descriptor for stdin */
  info.c_lflag &= ~ICANON;      /* disable canonical mode */
  info.c_cc[VMIN] = 1;          /* wait until at least one keystroke available */
  info.c_cc[VTIME] = 0;         /* no timeout */
  tcsetattr(0, TCSANOW, &info); /* set immediately */
}
void press_key()
{
  printf("\nPremi un tasto per continuare...\n");
  getchar();
}
int main(int argc, char**argv)
{
  init_press_key();
  printf("Numeri in singola precisione (float):\n");
  printf("epsilon (ovvero differenza minima)=\t%G\n", FLT_EPSILON);
  printf("massimo numero rappresentabile=\t\t%G\n", FLT_MAX);
  printf("minimo  numero rappresentabile=\t\t%G\n", FLT_MIN);
   
  printf("\nNumeri in doppia precisione (double):\n");
  printf("epsilon (ovvero differenza minima)=\t%G\n", DBL_EPSILON);
  printf("massimo numero rappresentabile=\t\t%G\n", DBL_MAX);
  printf("minimo  numero rappresentabile=\t\t%G\n", DBL_MIN);
    
  press_key();
  printf("ERRORE DI ARROTONDAMENTO\n\n");
  double a, b, c;
  a = 100000000;
  b = 1;
  c = 100000000;
  printf("a,b e c sono numeri in singola precisione\n");
  printf("a=%.0f\n", a);
  printf("b=%.0f\n", b);
  printf("c=%.0f\n", c);

  press_key();
  printf("1/(a+b-c)= %G\n", 1/(flt(a)+flt(b)-flt(c)));

  press_key();
  printf("1/(a-c+b)= %G\n", 1/(flt(a) - flt(c) + flt(b)));

  printf("\nPremi un tasto per continuare...\n");
  printf("\nOVERFLOW\n\n");
  a = 2E38;
  b = 2E38;
  c = 1E20;
  printf("a=%.0e\n", a);
  printf("b=%.0e\n", b);
  printf("c=%.0e\n", c);
  printf("(a+b)/c= %G\n", (flt(a)+flt(b))/flt(c));

  press_key();
  printf("a/c+b/c= %G\n", flt(a)/flt(c)+flt(b)/flt(c));
  return 0;
}
