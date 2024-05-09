#include <stdio.h>
#include <omp.h>

#define SIZE 512

int main()
{
    int a[SIZE][SIZE], b[SIZE][SIZE], mult[SIZE][SIZE], i, j, k;

    // Initialize matrices a and b with some values
    for (i = 0; i < SIZE; ++i)
        for (j = 0; j < SIZE; ++j)
        {
            a[i][j] = i + j;
            b[i][j] = i - j;
        }

    // Initialize matrix mult with zeros
    for (i = 0; i < SIZE; ++i)
        for (j = 0; j < SIZE; ++j)
        {
            mult[i][j] = 0;
        }

    // Multiplying matrices a and b and storing in array mult
    for (i = 0; i < SIZE; ++i)
        for (j = 0; j < SIZE; ++j)
            for (k = 0; k < SIZE; ++k)
            {
                mult[i][j] += a[i][k] * b[k][j];
            }

    // Displaying the multiplication of two matrices
    printf("Output Matrix:\n");
    for (i = 0; i < SIZE; ++i)
        for (j = 0; j < SIZE; ++j)
        {
            printf("%d  ", mult[i][j]);
            if (j == SIZE - 1)
                printf("\n\n");
        }

    return 0;
}