import math

# An example function whose solution
# is determined using Bisection Method.
def func6(x):
    return x * math.sin(x) + math.cos(x)


def derivFunc6(x):
    return x * math.cos(x)


def func7(x):
    return x - pow(math.e, -x)


def derivFunc7(x):
    return 1 + pow(math.e, -x)


def func9(x):
    return x * math.tan(x) + 1


def derivFunc9(x):
    return x * (1 + pow(math.tan(x), 2)) + math.tan(x)

# Function to find the root
def newtonRaphson(func, derivFunc, x):
    h = func(x) / derivFunc(x)
    while abs(h) >= 0.0001:
        h = func(x)/derivFunc(x)

        # x(i+1) = x(i) - f(x) / f'(x)
        x = x - h

    print("The value of the root is : ", "%.4f" % x)


# Driver program to test above
# Q6
x0 = math.pi  # Initial values assumed
newtonRaphson(func6, derivFunc6, x0)

# Driver program to test above
# Q7
x0 = 1  # Initial values assumed
newtonRaphson(func7, derivFunc7, x0)

# Driver program to test above
# Q9
x0 = 2.5  # Initial values assumed
newtonRaphson(func9, derivFunc9, x0)
