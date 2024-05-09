#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(int argc, char *argv[]);

/******************************************************************************/

int main(int argc, char *argv[])

/******************************************************************************/
/*
  Purpose:

    HELLO has each thread print out its ID.

  Discussion:

    HELLO is a "Hello, World" program for OpenMP.

    But we demonstrate a few simple features of OpenMP, including:

    How you get the "include" file.
    How you measure wall clock time.
    How you find out how many processors are available.
    How you find out which thread you are in a parallel section.
    How you find out how many threads are available in a parallel section.
    How you set the number of threads.
*/
{
    int id;
    int proc_num;
    int thread_num;
    double wtime;
    double wtime1;
    double wtime2;

    printf("\n");
    printf("HELLO\n");
    printf("  C/OpenMP version\n");

    wtime1 = omp_get_wtime();
    /*
      How many processors are available?
    */
    proc_num = omp_get_num_procs();

    printf("\n");
    printf("  The number of processors available:\n");
    printf("  OMP_GET_NUM_PROCS () = %d\n", proc_num);
/*
  How many threads are available by default or environment setting?
*/
#pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
        thread_num = omp_get_num_threads();

        if (id == 0)
        {
            printf("\n");
            printf("  Calling OMP_GET_NUM_THREADS inside a\n");
            printf("  parallel region, we get the number of\n");
            printf("  threads is %d\n", thread_num);
        }
        printf("  This is process %d out of %d\n", id, thread_num);
    }
    /*
      Request double the number of threads.
    */
    thread_num = 2 * thread_num;

    printf("\n");
    printf("  We request %d threads.\n", thread_num);

    omp_set_num_threads(thread_num);
/*
  Now how many threads do we see?
*/
#pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
        thread_num = omp_get_num_threads();

        if (id == 0)
        {
            printf("\n");
            printf("  Calling OMP_GET_NUM_THREADS inside a\n");
            printf("  parallel region, we get the number of\n");
            printf("  threads is %d\n", thread_num);
        }
        printf("  This is process %d out of %d\n", id, thread_num);
    }
    /*
      Finish up by measuring the elapsed time.
    */
    wtime2 = omp_get_wtime();
    wtime = wtime2 - wtime1;

    printf("\n");
    printf("HELLO\n");
    printf("  Normal end of execution.\n");

    printf("\n");
    printf("  Elapsed wall clock time = %f\n", wtime);

    return 0;
}