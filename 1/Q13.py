# Gauss Seidel Iteration

# Defining equations to be solved
# in diagonally dominant form
def f1(x, y, z): return (-2*y+2*z)/4
def f2(x, y, z): return (7 - x + z)/(-3)
def f3(x, y, z): return (5-3*x+y)/4


# Initial setup
x0 = 0
y0 = 0
z0 = 0

# Reading tolerable error
e = 0.0000001

# Implementation of Gauss Seidel Iteration
MAX_ITER = 9
for i in range(MAX_ITER):
    x1 = f1(x0, y0, z0)
    y1 = f2(x1, y0, z0)
    z1 = f3(x1, y1, z0)
    # print('%d\t%0.4f\t%0.4f\t%0.4f\n' %(count, x1,y1,z1))

    x0 = x1
    y0 = y1
    z0 = z1

print("Gauss-Siedal after 9 iteration")
print('Solution: x=%0.3f, y=%0.3f and z = %0.3f\n' % (x1, y1, z1))


# Gauss Jacobi
# Defining equations to be solved
# in diagonally dominant form
def f1(x, y, z): return (-2*y+2*z)/4
def f2(x, y, z): return (7 - x + z)/(-3)
def f3(x, y, z): return (5-3*x+y)/4


# Initial setup
x0 = 0
y0 = 0
z0 = 0
count = 1

# Reading tolerable error
e = 0.0000001

# Implementation of Jacobi Iteration

# condition = True
MAX_ITER = 20
for i in range(MAX_ITER):
    x1 = f1(x0, y0, z0)
    y1 = f2(x0, y0, z0)
    z1 = f3(x0, y0, z0)

    x0 = x1
    y0 = y1
    z0 = z1

print("Gauss-Jacobi after 20 iteration")
print('Solution: x=%0.3f, y=%0.3f and z = %0.3f\n' % (x1, y1, z1))
