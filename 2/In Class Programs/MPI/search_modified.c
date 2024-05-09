#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "mpi.h"

int main();
int search(int a, int b, int c);
int f(int i);

/******************************************************************************/

int main(int argc, char *argv[])

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for SEARCH.
*/
{
    int a;
    int b;
    int c;
    int fj;
    int i4_huge = 2147483647;
    int j;
    double wtime = 0.0;
    int ierr;
    int p_num;
    int id;

    a = 1;
    b = i4_huge;
    c = 45;

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

    if (id == 0)
    {

        printf("\n");
        printf("SEARCH:\n");
        printf("  C version\n");
        printf("  Search the integers from A to B\n");
        printf("  for a value J such that F(J) = C.\n");
        printf("\n");
        printf("  A           = %d\n", a);
        printf("  B           = %d\n", b);
        printf("  C           = %d\n", c);
    }

    /* wtime = ?; */

    j = search(a, b, c);

    /* wtime = ? - wtime */;

    if (id == 0)
    {

        if (j == -1)
        {
            printf("\n");
            printf("  No solution was found.\n");
        }
        else
        {
            printf("\n");
            printf("  Found     J = %d\n", j);
            printf("  Verify F(J) = %d\n", f(j));
        }

        wtime = MPI_Wtime() - wtime;
        printf("  Elapsed CPU time is %g\n", wtime);
        /*
          Terminate.
        */
        printf("\n");
        printf("SEARCH:\n");
        printf("  Normal end of execution.\n");
    }

    ierr = MPI_Finalize();

    return 0;
}
/******************************************************************************/

int search(int a, int b, int c)

/******************************************************************************/
/*
  Purpose:

    SEARCH searches integers in [A,B] for a J so that F(J) = C.

  Parameters:

    Input, int A, B, the search range.

    Input, int C, the desired function value.

    Output, int SEARCH, the computed solution, or -1
    if no solution was found.
*/
{
    int fi;
    int i;
    int j;

    j = -1;

    for (i = a; i <= b; i++)
    {
        fi = f(i);

        if (fi == c)
        {
            j = i;
            break;
        }
    }

    return j;
}
/******************************************************************************/

int f(int i)

/******************************************************************************/
/*
  Purpose:

    F is the function we are analyzing.

  Parameters:

    Input, int I, the argument.

    Input, int F, the value.
*/
{
    int i4_huge = 2147483647;
    int j;
    int k;
    int value;

    value = i;

    for (j = 1; j <= 5; j++)
    {
        k = value / 127773;

        value = 16807 * (value - k * 127773) - k * 2836;

        if (value <= 0)
        {
            value = value + i4_huge;
        }
    }

    return value;
}