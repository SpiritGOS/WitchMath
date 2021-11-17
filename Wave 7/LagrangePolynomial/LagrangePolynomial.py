import sympy as sp
import numpy as np
import math
import matplotlib.pyplot as plt
from sympy.core.singleton import S

def GetInterNodes(prime_func, args):
    x = sp.symbols('x')
    function = sp.sympify(prime_func)
    InterpolationNodes = [[], []]
    for arg in args:
        InterpolationNodes[0].append(arg)
        InterpolationNodes[1].append(function.evalf(subs={x: arg}))
    return InterpolationNodes

def GetLagrangePolynomial(InterpolationNodes):
    Polynom = ''
    for i in range(len(InterpolationNodes[0])):
        Polynom += f'({InterpolationNodes[1][i]})*('
        for x in InterpolationNodes[0]:
            if x != InterpolationNodes[0][i]:
                Polynom += f'(x-{x})'
                if x != InterpolationNodes[0][-1]:
                    Polynom += '*'
        Polynom += ')/('
        for x in InterpolationNodes[0]:
            if x != InterpolationNodes[0][i]:
                Polynom += f'({InterpolationNodes[0][i]}-{x})'
                if x != InterpolationNodes[0][-1]:
                    Polynom += '*'
        Polynom += ')'
        
        if i < len(InterpolationNodes[0]) - 1:
            Polynom += ' + '
    Polynom = Polynom.replace(')*)', '))')
    return Polynom

if __name__ == "__main__":
    PrimeFunction = 'asin(x)+x'
    InterNodes = GetInterNodes(PrimeFunction, [-0.4 , -0.1, 0.2 , 0.5])
    # PrimeFunction = 'ln(x)+x'
    # InterNodes = GetInterNodes(PrimeFunction, [0.1, 0.5, 0.9, 1.3])
    LagrangePolynomial = sp.sympify(GetLagrangePolynomial(InterNodes))
    print(InterNodes)
    print(LagrangePolynomial)

    x = sp.symbols('x')
    graph = [[], []]

    NumOfPoints = 1024
    Step = abs(InterNodes[0][-1] - InterNodes[0][0]) / NumOfPoints

    print(f'Step: {Step}')
        
    for i in np.arange(InterNodes[0][0] , InterNodes[0][-1], Step):
        graph[0].append(i)
        graph[1].append(LagrangePolynomial.evalf(subs={x: i}))

    fig, (ax1,ax2) = plt.subplots(2, 1, sharex=True, sharey=True)
    ax1.plot(graph[0], graph[1], label= 'Interpolation', color = (0.9, 0.2, 0.9))
    ax2.plot(graph[0], GetInterNodes(PrimeFunction, graph[0])[1], label = 'Reference')
    ax1.legend()
    ax2.legend()
    plt.show()