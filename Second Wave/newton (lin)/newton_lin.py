import sympy
import numpy


def Newton_Lin(equations):
    vars = sympy.symbols('x y')
    f = sympy.sympify(equations)
    Jacob = sympy.zeros(len(f), len(vars))
    for i, fi in enumerate(f):
        for j, s in enumerate(vars):
            Jacob[i, j] = sympy.diff(fi, s)

    print(numpy.array(Jacob.tolist()))


if __name__ == "__main__":
    equations = ['2*x - cos(y)', '2*y - exp(x) - x']
    Newton_Lin(equations)
