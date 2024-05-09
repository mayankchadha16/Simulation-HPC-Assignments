#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(void);
void jacobi(int n, double a[], double b[], double x[], double x_old[]);
void r8vec_uniform_01(int n, int *seed, double r[]);

/******************************************************************************/

int main(void)

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for JACOBI.

  Licensing:

    This code is distributed under the GNU LGPL license.

*/
{
    double *a;
    double *b;
    int i;
    int j;
    int n = 5000;
    double row_sum;
    int seed;
    double *x;
    double *x_old;

    a = (double *)malloc(n * n * sizeof(double));
    b = (double *)malloc(n * sizeof(double));
    x = (double *)malloc(n * sizeof(double));
    x_old = (double *)malloc(n * sizeof(double));

    printf("\n");
    printf("JACOBI\n");
    printf("  C version\n");
    printf("  Number of threads = %d\n", omp_get_max_threads());
    printf("  Problem size N = %d\n", n);

    seed = 123456789;

    r8vec_uniform_01(n * n, &seed, a);

    for (i = 0; i < n; i++)
    {
        row_sum = 0.0;
        for (j = 0; j < n; j++)
        {
            row_sum = row_sum + fabs(a[i + j * n]);
        }
        a[i + i * n] = 1.0 + 2.0 * row_sum;
    }

    for (i = 0; i < n; i++)
    {
        x[i] = (double)(i + 1);
    }

    for (i = 0; i < n; i++)
    {
        b[i] = 0.0;
        for (j = 0; j < n; j++)
        {
            b[i] = b[i] + a[i + j * n] * x[j];
        }
    }

    r8vec_uniform_01(n, &seed, x);

    jacobi(n, a, b, x, x_old);

    free(a);
    free(b);
    free(x);
    free(x_old);

    return 0;
}
/******************************************************************************/

void jacobi(int n, double a[], double b[], double x[], double x_old[])

/******************************************************************************/
/*
  Purpose:

    JACOBI carries out the Jacobi iteration.

  Licensing:

    This code is distributed under the GNU LGPL license.

*/
{
    double axi;
    double diff;
    double diff_tol;
    int i;
    int it;
    int it_max = 100;
    int j;
    double r8_epsilon = 1.0E-14;
    double wtime;
    double wtime1;
    double wtime2;

    diff_tol = 0.0;
    for (i = 0; i < n; i++)
    {
        diff_tol = diff_tol + fabs(b[i]);
    }
    diff_tol = (diff_tol + 1.0) * r8_epsilon;

    wtime1 = omp_get_wtime();

    for (it = 1; it <= it_max; it++)
    {
#pragma omp parallel shared(a, b, n, x, x_old) private(axi, i, j)
        /*
          Note that we need a curly bracket to enclose our parallel region!
        */
        {

#pragma omp for
            for (i = 0; i < n; i++)
            {
                x_old[i] = x[i];
            }

#pragma omp for
            for (i = 0; i < n; i++)
            {
                axi = 0.0;
                for (j = 0; j < n; j++)
                {
                    axi = axi + a[i + j * n] * x_old[j];
                }
                x[i] = x_old[i] + (b[i] - axi) / a[i + i * n];
            }

            diff = 0.0;
#pragma omp for reduction(+ : diff)
            for (i = 0; i < n; i++)
            {
                diff = diff + fabs(x[i] - x_old[i]);
            }
        }
        /*
          End of the parallel region.
        */
        printf("  %8d  %14e\n", it, diff);

        if (diff <= diff_tol)
        {
            break;
        }
    }

    wtime2 = omp_get_wtime();
    wtime = wtime2 - wtime1;

    printf("\n");
    printf("DIFF     = %e\n", diff);
    printf("DIFF_TOL = %e\n", diff_tol);
    printf("Time     = %e\n", wtime);

    printf("\n");
    printf("  First 10 elements of estimated solution:\n");
    printf("\n");

    for (i = 0; i < 10; i++)
    {
        printf("  %8d  %14f\n", i, x[i]);
    }

    return;
}
/******************************************************************************/

void r8vec_uniform_01(int n, int *seed, double r[])

/******************************************************************************/
/*
  Purpose:

    R8VEC_UNIFORM_01 returns a unit pseudorandom vector.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Parameters:

    Input, int N, the number of entries in the vector.

    Input/output, int *SEED, a seed for the random number generator.

    Output, double R[N], the vector of pseudorandom values.
*/
{
    int i;
    int i4_huge = 2147483647;
    int k;

    if (*seed == 0)
    {
        printf("\n");
        printf("R8VEC_UNIFORM_01 - Fatal error!\n");
        printf("  Input value of SEED = 0.\n");
        exit(1);
    }

    for (i = 0; i < n; i++)
    {
        k = *seed / 127773;

        *seed = 16807 * (*seed - k * 127773) - k * 2836;

        if (*seed < 0)
        {
            *seed = *seed + i4_huge;
        }

        r[i] = (double)(*seed) * 4.656612875E-10;
    }

    return;
}