import sympy
from sympy.matrices import Matrix


def Newton_Lin(equations, x0=2, y0=2, eps = 0.0001):
    superVar = []
    vars = sympy.symbols('x y')
    f = sympy.sympify(equations)
    Jacob = sympy.zeros(len(f), len(vars))
    for i, fi in enumerate(f):
        for j, s in enumerate(vars):
            Jacob[i, j] = sympy.diff(fi, s)

    f = Matrix(f)
    Jacob_Inv = Jacob.inv()
    totalVars = Jacob_Inv * f
    iter = 1
    while True:
        answer = []
        for i in range(len(equations)):
            a = sympy.sympify(totalVars[i])
            a = a.subs([(vars[0], x0), (vars[1], y0)])
            answer.append(a.evalf())
        b = Matrix([x0, y0]) + (Matrix(answer)*(-1))
        superVar.append(b)
        x0, y0 = superVar[-1][0], superVar[-1][1]
        if iter >= 2:
            if  max(abs(superVar[-1][0] - superVar[-2][0]), abs(superVar[-1][1] - superVar[-2][1])) < eps:
                print(f'Ierations: {iter}')
                print(superVar[-1])
                return superVar
        iter += 1

if __name__ == "__main__":
    equations = ['2*x - cos(y)', '2*y - exp(x) - x']
    test = ['x**2 + y**2 - 4', 'x**2 - y']
    test2 = ['x-2*y**2+1','-1*x**2+2*y-1']
    Newton_Lin(test)
