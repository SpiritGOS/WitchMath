import sympy as sp
import numpy as np
import matplotlib.pyplot as plt
import sys
import os
sys.path.insert(0, "Wave 1\\Gauss")

from Gauss import Gauss

def SqrApr(Nodes):
    syst=[[],[],[]]
    # 1
    for j in range(4, 1, -1):
        tmp = 0
        for i in range(len(Nodes[0])):
            tmp += Nodes[0][i]**j
        syst[0].append(tmp)
    tmp = 0
    for i in range(len(Nodes[0])):
        tmp += Nodes[0][i]**2*Nodes[1][i]
    syst[0].append(tmp)
    # 2
    for j in range(3, 0, -1):
        tmp = 0
        for i in range(len(Nodes[0])):
            tmp += Nodes[0][i]**j
        syst[1].append(tmp)
    tmp = 0
    for i in range(len(Nodes[0])):
        tmp += Nodes[0][i]*Nodes[1][i]
    syst[1].append(tmp)
    # 3
    for j in range(2, 0, -1):
        tmp = 0
        for i in range(len(Nodes[0])):
            tmp += Nodes[0][i]**j
        syst[2].append(tmp)
    tmp = 0
    syst[2].append(len(Nodes[0]))
    for i in range(len(Nodes[0])):
        tmp += Nodes[1][i]
    syst[2].append(tmp)

    f = open('C:\\Users\\marse\\Documents\\Проекты\\WitchMath\\Wave 9\\Matrix.txt', 'w+')
    for item in syst:
        f.write(str(item).replace(',', '').replace('[', '').replace(']', '\n'))
    f.seek(f.tell() - 1, os.SEEK_SET)
    f.write('')
    ABC = Gauss('C:\\Users\\marse\\Documents\\Проекты\\WitchMath\\Wave 9\\')
    poly = f'P(x) = ({ABC[0]})*x^2 + ({ABC[1]})*x + ({ABC[2]})'
    print(poly)
    return poly

def LinApr(Nodes):
    syst =[[], []]
    # 1
    for j in range(2, 0, -1):
        tmp = 0
        for i in range(len(Nodes[0])):
            tmp += Nodes[0][i]**j
        syst[0].append(tmp)
    tmp = 0
    for i in range(len(Nodes[0])):
        tmp += Nodes[0][i]*Nodes[1][i]
    syst[0].append(tmp)
    # 2
    tmp = 0
    for i in range(len(Nodes[0])):
        tmp += Nodes[0][i]
    syst[1].append(tmp)
    syst[1].append(len(Nodes[0]))
    tmp = 0
    for i in range(len(Nodes[0])):
        tmp += Nodes[1][i]
    syst[1].append(tmp)

    f = open('C:\\Users\\marse\\Documents\\Проекты\\WitchMath\\Wave 9\\Matrix.txt', 'w+')
    for item in syst:
        f.write(str(item).replace(',', '').replace('[', '').replace(']', '\n'))
    f.seek(f.tell() - 1, os.SEEK_SET)
    f.write('')
    ABC = Gauss('C:\\Users\\marse\\Documents\\Проекты\\WitchMath\\Wave 9\\')
    poly = f'P(x) = ({ABC[0]})*x + ({ABC[1]})'
    print(poly)
    return poly

if __name__ == "__main__":
    # 2
    Nodes = [
        [-1.0, 0.0, 1.0, 2.0, 3.0, 4.0],                          # x
        [0.86603, 1.0, 0.86603, 0.5, 0.0, -0.5]                   # y
    ]
    # # 16
    # Nodes = [
    #     [0.1, 0.5, 0.9, 1.3, 1.7, 2.1],                         # x
    #     [-2.2026, -0.19315, 0.79464, 1.5624, 2.2306, 2.8419]    # y
    # ]
    # # 19
    # Nodes = [
    #     [-0.7, -0.4, -0.1, 0.2, 0.5, 0.8],                      # x
    #     [-1.4754, -0.81152, -0.20017, 0.40136, 1.0236, 1.7273]  # y
    # ]

    SP = SqrApr(Nodes)
    LP = LinApr(Nodes)

    SqrPolynomial = sp.sympify(SP[7:])
    LinPolynomial = sp.sympify(LP[7:])

    x = sp.symbols('x')

    SqrGraph = [[], []]
    LinGraph = [[], []]

    NumOfPoints = 1024
    Step = abs(Nodes[0][-1] - Nodes[0][0]) / NumOfPoints

    print(f'Step: {Step}')
        
    for i in np.arange(Nodes[0][0] , Nodes[0][-1], Step):
        SqrGraph[0].append(i)
        SqrGraph[1].append(SqrPolynomial.evalf(subs={x: i}))
    for i in np.arange(Nodes[0][0] , Nodes[0][-1], Step):
        LinGraph[0].append(i)
        LinGraph[1].append(LinPolynomial.evalf(subs={x: i}))

    fig, (ax1,ax2) = plt.subplots(2, 1, sharex=True, sharey=True)
    ax1.plot(SqrGraph[0], SqrGraph[1], label = SP, color = (0.9, 0.2, 0.9))
    ax2.plot(LinGraph[0], LinGraph[1], label = LP)
    ax1.legend()
    ax2.legend()
    plt.show()