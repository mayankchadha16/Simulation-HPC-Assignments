import math

MAX_ITER = 1000

def func(x):
    return (7 + math.log10(x)) / 2


def iteration(a):
    for i in range(MAX_ITER):
        a = func(a)

    print("The value of root is : ", '%.4f' % a)


iteration(1)
