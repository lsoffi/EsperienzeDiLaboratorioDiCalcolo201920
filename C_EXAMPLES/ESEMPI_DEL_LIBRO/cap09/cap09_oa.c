/* Introduciamo le strutture, ripassiamo l'I/O
/* e le funzioni, impariamo ad evitare gli effetti */
/* collaterali nell'uso di funzioni */

#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS       0
#define EXIT_FAILURE      -9
#define EULER              0
#define EULER_CROMER       1

/* Notate che il punto e virgola alla fine */
/* delle prossime righe e' cruciale! */

struct phaseSpace {
  double x; 
  double v;
};
     
/* I PROTOTIPI */
     
/* m_ nelle righe sotto ci ricorda che si */
/* tratta di variabili mute, li' solo per */
/* memoria (potremmo non metterle nel prototipo, */
/* ma indicare solo il tipo) */
/* in questo esempio usiamo p per i puntatori */
     
struct phaseSpace *initHarmonicOscillator(double m_x0, 
					  double m_v0);
struct phaseSpace *euler(double m_dt, double m_omega2, 
			 struct phaseSpace *m_pXAndV);
struct phaseSpace *eulerCromer(double m_dt, double m_omega2, 
			       struct phaseSpace *m_pXAndV);

/* notate che energy() e' generica, */
/* mentre forceHarmonicOscillator() e' proprio per */
/* l'oscillatore armonico (da cui il nome) */

double energy(double m_omega2, struct phaseSpace *m_pXAndV);
double forceHarmonicOscillator(double m_omega2, double m_x);
double potentialEnergyHarmonicOscillator(double m_omega2, 
					 double m_x);
double myReadDouble(char *m_printMessage);
long   myReadLong(char *m_printMessage);

/*********************************/
int main(void) {
  double x0, v0, dt, omega2, totalTime, energy0, energy1;
  long   numberOfSteps, algorithm, i;
  struct phaseSpace xAndV;

  /* I simboli # sono per far piacere a gnuplot, per */
  /* esempio, o ad aiutarci ad usare un filtro per eliminare */
  /* le righe che non ci serviranno nella grafica */

  printf("# Integrazione Oscillatore Armonico\n");
  printf("#v1.1.1, 30 settembre 2005\n");

  /* queste myRead sono li' per evitarci un po' di codice... */

  totalTime = 
    myReadDouble(
       "Inserire il tempo totale di integrazione");
  algorithm = 
    myReadLong("Inserire 0 per Eulero, 1 per Eulero-Cromer");
  dt = myReadDouble("Inserire dt");
  x0 = myReadDouble("Inserire x0");
  v0 = myReadDouble("Inserire v0");
  omega2 = myReadDouble("Inserire omega2");

  /* Il cast lo facciamo noi esplicitamente, per tenere */
  /* le cose sotto controllo!! */

  numberOfSteps = (long)(totalTime/dt); 
  printf("# dt = %g tempo totale = %g\n",
	 dt, totalTime);
  printf("# omega2 = %g numero passi = %d\n",
	 omega2, numberOfSteps);

  /* una funzione senza effetti collaterali. quel */
  /* che cambia lo cambia con = */

  xAndV = *initHarmonicOscillator(x0, v0); 
  printf("# Condizioni iniziali x0 = %g v0 = %g\n", 
	 xAndV.x, xAndV.v);
  energy0 = energy(omega2, &xAndV);
  printf("# L'energia al tempo t = 0 vale %g\n", energy0);
  if (algorithm == EULER) {
    printf("# Usiamo l'algoritmo di Eulero\n");
    for (i = 0; i < numberOfSteps; i++) {

      /* un'altra funzione senza effetti collaterali... */

      xAndV = *euler(dt, omega2, &xAndV);
      energy1 = energy(omega2, &xAndV);
      printf("%g %g %g %g\n", 
	     (double)i*dt, xAndV.x, xAndV.v, energy1 - energy0);
    }
  } else if (algorithm == EULER_CROMER) {
    printf("# Usiamo l'algoritmo di Eulero-Cromer\n");
    for (i = 0; i < numberOfSteps; i++) {

      /* un'altra funzione senza effetti collaterali... */

      xAndV = *eulerCromer(dt, omega2, &xAndV);
      energy1 = energy(omega2, &xAndV);
      printf("%g %g %g %g\n", 
	     (double)i*dt, xAndV.x, xAndV.v, energy1 - energy0);
    }
  } else {
    printf("# TUONI E FULMINI:");
    printf("L'algoritmo n. %ld non e' implementato. Errore.\n",
	   algorithm);
    exit(EXIT_FAILURE);
  }
  energy1 = energy(omega2, &xAndV);
  printf("# L'energia al tempo t = %d vale %g\n",
         numberOfSteps, energy1);
  return EXIT_SUCCESS;
}

/*********************************/
struct phaseSpace  *initHarmonicOscillator(double x0, 
					   double v0) {
  static struct phaseSpace xAndV; 
  xAndV.x = x0;
  xAndV.v = v0;
  return &xAndV;
}

/*********************************/
struct phaseSpace *euler(double dt, double omega2, 
                         struct phaseSpace *pXAndVOld) {
  static struct phaseSpace xAndVNew;

  /* che succede se omettete le prime parentesi */
  /* nella riga sotto ?*/

  xAndVNew.v = (*pXAndVOld).v + 
    forceHarmonicOscillator(omega2, (*pXAndVOld).x) * dt;

  /* perche' qui usiamo -> e non . ? */

  xAndVNew.x = pXAndVOld->x + pXAndVOld->v * dt;
  return &xAndVNew;
}

/*********************************/
struct phaseSpace *eulerCromer(double dt, double omega2, 
			        struct phaseSpace *pXAndVOld) {

/* Qual e' la differenza fra Eulero ed Eulero-Cromer? */

  static struct phaseSpace xAndVNew;
  xAndVNew.v = (*pXAndVOld).v + 
    forceHarmonicOscillator(omega2, (*pXAndVOld).x) * dt;
  xAndVNew.x = pXAndVOld->x + xAndVNew.v * dt;
  return &xAndVNew;
}

/*********************************/
double energy(double omega2, struct phaseSpace *pXAndV) {

/* Calcoliamo in realta' 2 E / m */

  double localEnergy;
  localEnergy = (*pXAndV).v * (*pXAndV).v 
    + potentialEnergyHarmonicOscillator(omega2, (*pXAndV).x);
  return localEnergy;
}

/*********************************/
double forceHarmonicOscillator(double omega2, double x) {
  return - omega2 * x;
}

/*********************************/
double potentialEnergyHarmonicOscillator(double omega2, 
                                         double x) {
  return omega2 * x * x;
}

/*********************************/
long myReadLong(char *printMessage) {
  long inputData;

  printf("# %s\n",printMessage); 
  fflush(stdout);
  scanf("%ld",&inputData);

  return inputData;
}

/*********************************/
double myReadDouble(char *printMessage) {
  double inputData;

  printf("# %s\n",printMessage); fflush(stdout);
  scanf("%lg", &inputData);

  return inputData;
}
