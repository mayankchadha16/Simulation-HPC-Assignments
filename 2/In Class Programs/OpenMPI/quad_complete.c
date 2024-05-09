#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
/*
  CHANGE 1) Include the OMP.H file here;
# include <omp.h>
*/
#include <omp.h>

/******************************************************************************/

int main(int argc, char *argv[])

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for QUAD.

  Discussion:

    QUAD is a C program to estimate the integral of
      f = 50.0 / ( pi * ( 2500.0 * x[i] * x[i] + 1.0 ) )
    between 0 and 10.

    If you modify the program in 4 places, it should run correctly
    under OpenMP.

    If you can do that, then compare the execution time when you
    use 1, 2, 4 or 8 threads.

    export OMP_NUM_THREADS=1    Wallclock time   = 0.004404
    export OMP_NUM_THREADS=2    Wallclock time   = 0.002128
    export OMP_NUM_THREADS=4    Wallclock time   = 0.001839
    export OMP_NUM_THREADS=8    Wallclock time   = 0.001736
*/
{
    double a = 0.0;
    double b = 10.0;
    double error;
    double exact = 0.49936338107645674464;
    int i;
    int n = 1000000;
    double pi = 3.141592653589793;
    double total;
    double wtime = 0.0;
    double *x;

    printf("\n");
    printf("QUAD:\n");
    printf("  C version\n");
    printf("\n");
    printf("  Estimate the integral of f(x) from A to B.\n");
    printf("  f(x) = 50 / ( pi * ( 2500 * x * x + 1 ) ).\n");
    printf("  A = %f\n", a);
    printf("  B = %f\n", b);
    printf("  Exact integral from 0 to 10 is 0.49936338107645674464...\n");
    /*
      Load the array X with evenly spaced values between A and B.
    */
    x = (double *)malloc(n * sizeof(double));

    for (i = 0; i < n; i++)
    {
        x[i] = ((double)(n - i - 1) * a + (double)(i)*b) / (double)(n - 1);
    }
    /*
      Evaluate F at each node, sum and average.
    */
    /*
      CHANGE 2) Use the OpenMP timer here to initialize WTIME.
    */

    /* wtime = ??? */
    wtime = omp_get_wtime();

    total = 0.0;
    /*
      CHANGE 3) Fill in these two OpenMP directives here.
    */

#pragma omp parallel private(i) shared(x, n, a, b, pi) reduction(+ : total)
    {
#pragma omp for
        for (i = 0; i < n; i++)
        {
            total = total + 50.0 / (pi * (2500.0 * x[i] * x[i] + 1.0));
        }
        total = (b - a) * total / (double)n;
    }
    /*
      CHANGE 4) Call the OpenMP timer here to update WTIME.
    */

    /*  wtime = ??? */
    wtime = omp_get_wtime() - wtime;

    /*
      Print quadrature estimate, error, time
    */
    error = fabs(total - exact);

    printf("\n");
    printf("  Estimate = %f\n", total);
    printf("  Error    = %e\n", error);
    printf("  Wallclock time   = %f\n", wtime);

    free(x);

    return 0;
}