import math

def newton_method(func, dfunc, ddfunc, eps = 0.01, a = -2, b = 2):
    try:
        if (func(a)*ddfunc(a)) > 0:
            c = a
        else:
            c = b
        count = 0
        while abs(func(c)) > eps:
            count += 1
            c = c - func(c) / dfunc(c)
        print(count)
        return c
    except ValueError:
        return 'Value not invalidate'

def func_16(x):
    return x * math.exp(x) + x ** 2 - 1

def dfunc_16(x):
    return x * math.exp(x) + math.exp(x) + 2 * x

def dfunc_16_d2(x):
    return x * math.exp(x) + 2 * math.exp(x) + 2

def func_19(x):
    return x**4-2*x-1

def d_func_19(x):
    return 4*x**3-2

def d2_func_19(x):
    return 12*x**2


if __name__ == '__main__':
    print(newton_method(func_16, dfunc_16, dfunc_16_d2, 0.001, 1, 2))
