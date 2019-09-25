void copy(double *src, double *dest, int n);
 
void add(double *x, double lambda, double *u, int n);

double input(double *x, int n);

double derivative(double (*f)(double *, int), double *x, int n, int m,
                  double epsilon);

double dFdLambda(double (*f)(double *, int), double *x, double *u, int n, 
		 double epsilon);

double dF2dLambda2(double (*f)(double *, int), double *x, double *u,
		   int n, double epsilon);

void gradient(double (*f)(double *, int), double *x, double *grad, int n,
              double epsilon);

void opposite(double *x, int n);

double norm(double *a, double *b, int n);

void linmin(double (*f)(double *, int), double *x, double *u, int n, 
	    double epsilon);

void dump(double *x, int n, int count, ...);
