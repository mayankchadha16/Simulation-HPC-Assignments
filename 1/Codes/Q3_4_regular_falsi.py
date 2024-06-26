import math
MAX_ITER = 1000000

# An example function whose solution
# is determined using Regular Falsi Method.
# The function is x^3 - 2x - 5
def func3(x):
    return (x * x * x - 2*x - 5)


def func4(x):
    return (math.cos(x) - x*math.exp(x))

# Prints root of func(x) in interval [a, b]
def regulaFalsi(func, a, b):
    if func(a) * func(b) >= 0:
        print("You have not assumed right a and b")
        return -1

    c = a  # Initialize result

    for i in range(MAX_ITER):

        # Find the point that touches x axis
        c = (a * func(b) - b * func(a)) / (func(b) - func(a))

        # Check if the above found point is root
        if func(c) == 0:
            break

        # Decide the side to repeat the steps
        elif func(c) * func(a) < 0:
            b = c
        else:
            a = c

    print("The value of root is : ", '%.4f' % c)


# Driver code to test above function
# Initial values assumed
# Q3
a = 2
b = 3
regulaFalsi(func3, a, b)

# Q4
a = 0
b = 1
regulaFalsi(func4, a, b)
