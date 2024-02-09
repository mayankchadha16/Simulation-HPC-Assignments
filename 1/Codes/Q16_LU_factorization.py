import scipy
import scipy.linalg
import numpy

numpy.set_printoptions(precision=2)

# Python3 Program to decompose
# a matrix into lower and
# upper triangular matrix
MAX = 100


def luDecomposition(mat, n):

    lower = [[0 for x in range(n)] for y in range(n)]
    upper = [[0 for x in range(n)] for y in range(n)]

    # Decomposing matrix into Upper
    # and Lower triangular matrix
    for i in range(n):

        # Upper Triangular
        for k in range(i, n):

            # Summation of L(i, j) * U(j, k)
            sum = 0
            for j in range(i):
                sum += (lower[i][j] * upper[j][k])

            # Evaluating U(i, k)
            upper[i][k] = mat[i][k] - sum

        # Lower Triangular
        for k in range(i, n):
            if (i == k):
                lower[i][i] = 1  # Diagonal as 1
            else:

                # Summation of L(k, j) * U(j, i)
                sum = 0
                for j in range(i):
                    sum += (lower[k][j] * upper[j][i])

                # Evaluating L(k, i)
                lower[k][i] = int((mat[k][i] - sum) / upper[i][i])

    P, L, U = scipy.linalg.lu(A)
    # setw is for displaying nicely
    print("Lower Triangular\t\t\tUpper Triangular")

    # Displaying the result :
    for i in range(n):

        # Lower
        for j in range(n):
            print("{:.2f}".format(L[i][j]), end="\t")
        print("", end="\t")

        # Upper
        for j in range(n):
            print("{:.2f}".format(U[i][j]), end="\t")
        print("")


# Driver code
mat = [[4, 1, 1],
       [1, 4, -2],
       [3, 2, -4]]
A = numpy.array(mat)

luDecomposition(mat, 3)
