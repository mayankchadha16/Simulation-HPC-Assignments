#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "mpi.h"
int main(int argc, char *argv[]);
int prime_part(int id, int p, int n);

int main(int argc, char *argv[])

/******************************************************************************/
/*
  Purpose:

    PRIME counts the prime numbers between 2 and N.

  Discussion:

    We divide the calculation up into P parts.

    Part 0   checks 2+0,   2+P+0,   2+2*P+0, ...
    Part 2   checks 2+1,   2+P+1,   2+2*P+1, ...
    Part P-1 checks 2+P-1, 2+2*P-1, 2+3*P-1, ...

    Right now, the outer loop executes all P parts.
    But it would be simple to make an MPI version, in which the
    program with identifier ID only executes part ID.

    Modify this program so that it runs under MPI.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    16 October 2013

  Author:

    John Burkardt
*/
{
    int id;
    int n = 100000;
    int p;
    int total;
    int total_part;
    double wtime;
    double q;
    double q_diff;
    double q_part;

    p = 4;

    total = 0;

    // int id;
    int ierr;
    int p_num;
    /*
      Initialize MPI.
    */
    ierr = MPI_Init(&argc, &argv);
    /*
      Get the number of processes.
    */
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &p_num);
    /*
      Get the individual process ID.
    */
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id);

    wtime = MPI_Wtime();
    // int ans;

    ierr = MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // if (id == 0)
    // {

    //     printf("\n");
    //     printf("PRIME:\n");
    //     printf("  C version\n");
    // }
    // for (id = 0; id < p; id++)
    // {
    total_part = prime_part(id, p_num, n);
    total = total + total_part;
    // }

    ierr = MPI_Reduce(&total_part, &total, 1, MPI_INT, MPI_SUM, 0,MPI_COMM_WORLD);
    if (id == 0)
    {
        printf("\n");
        printf("     Between 2 and %d, there are %d primes\n", n, total);
        wtime = MPI_Wtime() - wtime;
        printf("  Wall clock elapsed seconds = %f\n", wtime);
    }
    ierr = MPI_Finalize();

    return 0;
}
int prime_part(int id, int p, int n)
{
    int i;
    int j;
    int prime;
    int total_part;

    total_part = 0;

    for (i = 2 + id; i <= n; i = i + p)
    {
        prime = 1;

        for (j = 2; j < i; j++)
        {
            if (i % j == 0)
            {
                prime = 0;
                break;
            }
        }
        if (prime)
        {
            total_part = total_part + 1;
        }
    }

    return total_part;
}