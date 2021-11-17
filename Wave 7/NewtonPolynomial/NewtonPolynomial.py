import sympy as sp
import numpy as np
import matplotlib.pyplot as plt

def GetInterNodes(prime_func, args):
    x = sp.symbols('x')
    function = sp.sympify(prime_func)
    InterpolationNodes = [[], []]
    for arg in args:
        InterpolationNodes[0].append(arg)
        InterpolationNodes[1].append(function.evalf(subs={x: arg}))
    return InterpolationNodes

def GetNewtonPolynomial():
    pass

if __name__ == "__main__":
    pass