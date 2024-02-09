import math

# An example function whose
# solution is determined using
# Bisection Method.
# The function is x^3 - x - 1
def func1(x):
    return x*x*x - x - 1

# The function is xe^x - 1
def func2(x):
    return x*math.exp(x) - 1

# Prints root of func(x)
# with error of EPSILON
def bisection(func, a, b):

    if (func(a) * func(b) >= 0):
        print("You have not assumed right a and b\n")
        return

    c = a
    while ((b-a) >= 0.01):

        # Find middle point
        c = (a+b)/2

        # Check if middle point is root
        if (func(c) == 0.0):
            break

        # Decide the side to repeat the steps
        if (func(c)*func(a) < 0):
            b = c
        else:
            a = c

    print("The value of root is : ", "%.4f" % c)


# Driver code
# Initial values assumed
# Q1
a = 1
b = 2
bisection(func1, a, b)

# Q2
a = 0
b = 1
bisection(func2, a, b)
