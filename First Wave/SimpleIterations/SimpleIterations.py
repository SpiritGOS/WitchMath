def simple_iterations(matrix, eps):

    def printMatrix(matrix):
        for a in range(len(matrix)):
            for b in range(len(matrix[a])):
                print(str(round(matrix[a][b], 3)).ljust(5), end='\t')
            print('\n', end='')
        print('\n', end='')

    
    print('Исходная матрица:')
    printMatrix(matrix)
    size = len(matrix)
    Xn = [0] * size
    counter = 1
    x1 = [matrix[i][-1] / matrix[i][i] for i in range(size)]
    while True:
        for i in range(size): # Метод простых итераций
            Xn[i] = matrix[i][-1] / matrix[i][i]; # следующее приближение
            for j in range(size):
                if (i == j): # проверка на диаг. элемент
                    pass
                else:
                    Xn[i] -= matrix[i][j] / matrix[i][i] * x1[j] # вычисляем последующее приближение
        flag = True # считаем, что вектор решений изначально найден
        for i in range(size):
            if abs(Xn[i] - x1[i]) > eps:
                flag = False
                break 
        for i in range(size):
            x1[i] = Xn[i] # запись   значения последующего приближения в предыдущее для увелечения точности последующих приближений
        if flag: # Проверка на выход из бесконечного цикла
            break
        counter += 1
    print(f'Counter = {counter}')
    return Xn


if __name__ == '__main__':
    matrix = []
    eps = 0.001
    with open('C:\\Users\\marse\\OneDrive\\Документы\\Проекты\\Вычислительная математика\\First Wave\\SimpleIterations\\Matrix.txt', 'r') as f:
        for line in f:
            matrix.append([float(i) for i in line.split()])
    [
        print(f'x[{i+1}] = {x}')
            for i, x in enumerate(simple_iterations(matrix, eps))
        ]
