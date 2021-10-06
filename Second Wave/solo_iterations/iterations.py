from math import exp


def func_16(x):
    return x * exp(x) + x ** 2 - 1


def dfunc_16(x):
    return x * exp(x) + exp(x) + 2 * x


def gfunc_16(func, dfunc, a, b, x):
    max_ = dfunc(a)
    i = a
    while i <= b:
        max_ = max(max_, dfunc(i))
        i += 0.001
    l = 1/max_
    return x - l*func(x)


def dgfunc_16(dfunc, a, b, x):
    max_ = dfunc(a)
    i = a
    while i <= b:
        max_ = max(max_, dfunc(i))
        i += 0.001
    l = 1/max_
    return 1 - l*dfunc(x)


def func_19(x):
    return x**4-2*x-1


def dfunc_19(x):
    return 4*x**3-2


def gfunc_19(func, dfunc, a, b, x):
    max_ = dfunc(a)
    i = a
    while i <= b:
        max_ = max(max_, dfunc(i))
        i += 0.001
    l = 1/max_
    return x - l*func(x)


def dgfunc_19(dfunc, a, b, x):
    max_ = dfunc(a)
    i = a
    while i <= b:
        max_ = max(max_, dfunc(i))
        i += 0.001
    l = 1/max_
    return 1 - l*dfunc(x)


def iterations_method(func, dfunc, gfunc, dgfunc, a, b, eps):
    x = [b]
    new_x = b
    while abs(dgfunc(dfunc, a, b, new_x)) < 1:
        new_x = gfunc(func, dfunc, a, b, x[-1])
        x.append(new_x)
        if abs(func(new_x)) < eps and ((x[-1] - x[-2])**2/abs(2 * x[-2] - x[-1] - x[-3]) < eps if len(x) >= 3 else False):
            return new_x


if __name__ == "__main__":
    print(iterations_method(func_19, dfunc_19, gfunc_19, dgfunc_19, 0, 2, 0.001))
