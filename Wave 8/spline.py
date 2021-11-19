import sympy as sp
# Таблица значений X, Y. Так же H и Х*
TABLE_16 = (
    [0.1, 0.5, 0.9, 1.3, 1.7],
    [-2.8069, -0.193115, 0.79464, 1.5624, 2.2306]
)
X_16 = (0.8)
H_16 = (0.4)

TABLE_19 = (
    [-0.4, -0.1, 0.2, 0.5, 0.8],
    [-0.81152, -0.20017, 0.40136, 1.0236, 1.7273]
)
X_19 = 0.1
H_19 = 0.3


def coeffs(table, h):
    y = table[1]
    P = [0]
    Q = [0]
    result = []
    for i in range(1, len(y) - 1):
        new_y = ((y[i+1]-2*y[i]+y[i-1]))/h
        result.append(new_y)
        P.append(-h/(4*h+P[i-1]*h))
        Q.append((6*new_y-h*Q[i-1])/(4*h+P[i-1]*h))
    return result, Q, P


def find_m(Q, P):
    m = [0]
    for i in range(1, len(Q)):
        m.append(P[i]*m[i-1]+Q[i])
    m.append(0)
    return m


def find_S_node(table, h, m, X):
    y = table[1]
    x = table[0]
    i = -1
    for index, x_in_list in enumerate(x):
        if index != 0:
            if X < x_in_list:
                i = index
                break
    if i == -1:
        return -1
    s = (
        (m[i]*(X-x[i-1])+m[i-1]*(x[i]-X**3))/6*h +
        (y[i]-(m[i]*h**2)/6)*(X-x[i-1])/h +
        (y[i-1]-(m[i-1]*h**2)/6)*(x[i]-X)/h
    )
    return s

# #Вычислим прогоночные коэффициенты Q, P
# Y = [0, 0, -1.1978/0.9, 0.181/0.9, 0.0328/0.9]
# Q = [0, 0, 0, 0, 0, 0]
# P = [0, 0, 0, 0, 0, 0]

# for i in range(3,6):
# 	P[i] = -0.9 / (3.6 + P[i-1]*0.9)
# 	Q[i] = (6*Y[i-1] - 0.9*Q[i-1]) / (3.6 + P[i-1]*0.9)
# #print(f'P: {P}\nQ: {Q}')
# #Вычислим все m
# m = [0, 0, Q[5]]


# for i in range(1,-1,-1):
# 	m[i] = P[i+3] * m[i+1] + Q[i+3]
# #print (f'm: {m}')
# #Выведем кубический сплайн, а так же вычислим значение в точке Х*
# print(f'\n Кубический сплайн: {29/200}*x\u00B2 - {217/200}*x + {67517/20000}\n ')
# print(f" Значение кубического сплайна в точке {X} = {round((29/200*pow(X,2) - 217/200*X + 67517/20000), 5)}\n")
if __name__ == "__main__":
    Y, Q, P = coeffs(TABLE_19, H_19)
    m = find_m(Q, P)
    print(find_S_node(TABLE_19, H_19, m, X_19))
