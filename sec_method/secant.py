from math import exp

def func_16(x):
    return x * exp(x) + x ** 2 - 1

def func_19(x):
    return x**4-2*x-1

def secant(func, a, b, eps):
    cshki = [1, 2]
    while True:
        c = (a * func(b) - b * func(a))/(func(b)-func(a))
        if func(a) * func(c) < 0:
            b = c
        elif func(c) * func(b) < 0:
            a = c
        # print(cshki[-1], cshki[-2])
        
        if not (abs(func(c)) > eps) and (abs(cshki[-1] - cshki[-2]) > eps):
            return c

if __name__ == '__main__':
    print(secant(func_19, 0, 2, 0.001))