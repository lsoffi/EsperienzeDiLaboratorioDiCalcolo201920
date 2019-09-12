#include <stdlib.h>
#include <stdio.h>
int main()
{
  int ret, i, nc=0;
  FILE* fp;
  double data[][2] = {{1.0, 1.0},{2.0, 4.0},{3.0,4.0},{10.0, 100.0}};
 
  printf("\ndati da scrivere\n");
  for (i=0; i < 4; i++)
    {
      printf("%.15G %.15G\n", data[i][0], data[i][1]);
    } 

  printf("\n");
  fp = fopen("myfile.dat", "w");
  if (fp==NULL)
    {
      printf("C'è stato qualche problema nell'apertura del file!\n");
      exit(1);
    }

  for (i=0; i < 4; i++)
    {
      ret =  fprintf(fp, "%.15G %.15G\n", data[i][0], data[i][1]);
      if (ret < 0)
	{
	  printf("C'è stato qualche problema nella scrittura del file!\n");
	  exit(-1);
	}
      nc = nc + ret;
    }
  printf("Ho scritto n. %d caratteri\n", nc);

  // assicura che tutto sia scritto (in questo caso invero è inutile
  // poiché poi chiude il file
  fflush(fp); 

  fclose(fp);

  fp = fopen("myfile.dat", "r");
  if (fp==NULL)
    {
      printf("C'è stato qualche problema nell'apertura del file!\n");
      exit(1);
    }
  nc = 0;
  for (i=0; i < 4; i++)
    nc += fscanf(fp, "%lf %lf\n", &(data[i][0]), &(data[i][1]));

  if (nc < 8)
    {
      printf("C'è stato qualche problema nella lettura del file!\n");
      exit(-1);
    }
  printf("\nHo letto n. %d elementi\n", nc);

  fclose(fp);

  printf("\ndati letti\n");
  for (i=0; i < 4; i++)
    {
      printf("%.15G %.15G\n", data[i][0], data[i][1]);
    }
}
