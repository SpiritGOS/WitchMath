import random as r
import math


def printMatrix(matrix):
    for a in range(len(matrix)):
        for b in range(len(matrix[a])):
            print(str(round(matrix[a][b], 3)).ljust(5), end='\t')
        print('\n', end='')
    print('\n', end='')


def Gauss(way=''):
    # Считываем матрицу из файла
    f = open(way+'Matrix.txt', 'r')
    matrix = []
    for line in f:
        matrix.append(list(map(float, line.split())))
    f.close()
    print('Исходная матрица:')
    printMatrix(matrix)
    # Добавляем к матрице столбец с контрольными суммами
    for i in range(len(matrix)):
        if matrix[i][i] == 0:
            rand = 0
            while matrix[rand][i] == 0:
                rand = r.randint(i, len(matrix))
            matrix[i], matrix[rand] = matrix[rand], matrix[i]
        # Формируем числа для обнуления элементов ниже ведущего
        for j in range(i + 1, len(matrix)):
            destr = (-1 * matrix[j][i] / matrix[i][i])
            # Обнуляем числа ниже ведущего элемента
            for k in range(0, len(matrix[j])):
                matrix[j][k] = matrix[j][k] + matrix[i][k] * destr
        print(f'Прямой Проход №{i + 1}:')
        printMatrix(matrix)
    # Прямой ход алгоритма Гаусса завершен
    # Начинаем обратный ход с формирования массива неизвестных
    result = []
    for i, string in reversed(list(enumerate(matrix))):
        tmp = sum(string[i+1:-1])
        result.append((string[-1] - tmp) / string[i])
        for j in range(i - 1, -1, -1):
            matrix[j][i] = matrix[j][i] * result[-1]
        print(f'Обратный Проход №{len(matrix) - i}:')
        printMatrix(matrix)
    result.reverse()
    print("Итоговые ответы:")
    for index, elem in enumerate(result):
        print(f'X[{index + 1}] = {round(elem, 3)}')
    return result

if __name__ == "__main__":
    Gauss()
