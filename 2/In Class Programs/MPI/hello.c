#include <stdlib.h>
#include <stdio.h>

#include "mpi.h"

/*
  Purpose:
    MAIN is the main program for HELLO.
*/
int main(int argc, char *argv[])
{
  int id;
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
  /*
    Process 0 prints an introductory message.
  */
  if (id == 0)
  {
    printf("\n");
    printf("HELLO - Master process:\n");
    printf("  C version\n");
    printf("  An MPI example program.\n");
    printf("\n");
    printf("  The number of processes is %d.\n", p_num);
    printf("\n");
  }
  /*
    Every process prints a hello.
  */
  printf("  Hello from process %d\n", id);
  /*
    Shut down MPI.
  */
  ierr = MPI_Finalize();

  return 0;
}