from typing import Sized
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

def FormFraction(args , results):
    if len(args) > 2:
        Fraction = f'((({FormFraction(args[1:], results[1:])}) - ({FormFraction(args[:-1], results[:-1])})) / (({args[-1]}) - ({args[0]})))'
    else:
        Fraction = f'((({results[1]}) - ({results[0]})) / (({args[1]}) - ({args[0]})))'
    return Fraction

def GetNewtonPolynomial(InterpolationNodes):
    Polynom = f'({InterpolationNodes[1][0]}) + '
    for i in range(1, len(InterpolationNodes[0])):
        Polynom += f'{(FormFraction(InterpolationNodes[0][:i+1], InterpolationNodes[1][:i+1]))} * '
        for j in range(i):
            Polynom += f'(x - ({InterpolationNodes[0][j]})) * '
        Polynom = Polynom[:-3]
        Polynom += ' + '
    Polynom = Polynom[:-3]
    return Polynom

if __name__ == "__main__":
    # PrimeFunction = 'asin(x)+x'
    # InterNodes = GetInterNodes(PrimeFunction, [-0.4 , -0.1, 0.2 , 0.5])
    PrimeFunction = 'ln(x)+x'
    InterNodes = GetInterNodes(PrimeFunction, [0.1, 0.5, 0.9, 1.3])
    NewtonPolynomial = sp.sympify(GetNewtonPolynomial(InterNodes))
    print(InterNodes)
    print(NewtonPolynomial)

    x = sp.symbols('x')
    graph = [[], []]

    NumOfPoints = 1024
    Step = abs(InterNodes[0][-1] - InterNodes[0][0]) / NumOfPoints

    print(f'Step: {Step}')
        
    for i in np.arange(InterNodes[0][0] , InterNodes[0][-1], Step):
        graph[0].append(i)
        graph[1].append(NewtonPolynomial.evalf(subs={x: i}))

    fig, (ax1,ax2) = plt.subplots(2, 1, sharex=True, sharey=True)
    ax1.plot(graph[0], graph[1], label= 'Interpolation', color = (0.9, 0.2, 0.9))
    ax2.plot(graph[0], GetInterNodes(PrimeFunction, graph[0])[1], label = 'Reference')
    ax1.legend()
    ax2.legend()
    plt.show()