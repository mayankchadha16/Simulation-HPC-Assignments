
# Defining our function as seidel which takes 3 arguments
# as A matrix, Solution and B matrix

def seidel(a, x, b):
    n = len(a)
    for j in range(0, n):
        # temp variable d to store b[j]
        d = b[j]

        # to calculate respective xi, yi, zi
        for i in range(0, n):
            if (j != i):
                d -= a[j][i] * x[i]
        # updating the value of our solution
        x[j] = d / a[j][j]
    # returning our updated solution
    return x


# int(input())input as number of variable to be solved
n = 8
a = []
b = []
# initial solution depending on n(here n=3)
x = [0, 0, 0, 0, 0, 0, 0, 0]
a = [[4, 1, -1, 0, 0, 0, 0, 0], [1, 6, -2, 1, -1, 0, 0, 0], [0, 1, 5, 0, -1, 1, 0, 0], [0, 2, 0, 5, -1, 0, -1, -1],
     [0, 0, -1, -1, 6, -1, 0, -1], [0, 0, -1, 0, -1, 5, 0, 0], [0, 0, 0, -1, 0, 0, 4, -1], [0, 0, 0, -1, -1, 0, -1, 5]]
b = [3, -6, -5, 0, 12, -12, -2, 2]
print(x)

# loop run for m times depending on m the error value
for i in range(0, 50):
    x = seidel(a, x, b)
    # print each time the updated solution
print(x)


