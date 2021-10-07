def Progonka():
    var = []
    file = open('C:\\Users\\marse\\OneDrive\\Документы\\Проекты\\Вычислительная математика\\First Wave\\Progonka\\Matrix.txt', 'r')
    for line in file:
        var.append(list(map(float, line.split())))
    file.close()
    A = []
    B = []
    # Прогоночные коэффициенты для первой строки
    A.append(-1 * var[0][1] / var[0][0])
    B.append(var[0][2] / var[0][0])
    # Прогоночные коэффициенты для последующих строк, исключая последнюю
    for i in range(1, len(var)-1):
        A.append(-1 * var[i][2] / (var[i][1] + var[i][0] * A[-1]))
        B.append((var[i][3] - var[i][0] * B[-1]) /
                 (var[i][1] + var[i][0] * A[-2]))
    # Прогоночные коэффициенты для последней строки
    A.append(0)
    B.append((var[len(var)-1][2] - var[len(var)-1][0] * B[-1]) /
             (var[len(var)-1][1] + var[len(var)-1][0] * A[-2]))
    # Прямой ход закончен
    #
    result = []
    for index, elem in reversed(list(enumerate(var))):
        if index != len(var) - 1:
            result.append(A[index] * result[-1] + B[index])
        else:
            result.append(B[index])
    # Итоговый результат
    result.reverse()
    for index, elem in enumerate(result):
        print(f'X[{index + 1}] = {round(elem, 3)}')


Progonka()
