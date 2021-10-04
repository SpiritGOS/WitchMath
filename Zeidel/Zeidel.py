def zeidel(matrix, eps):
    """
        Держу в курсе, пилил по черкасову, остановился на 26 странице,
        на моменте определения старых и новых Х
    """
    size = len(matrix)

    def printMatrix(matrix):
        for a in range(size):
            for b in range(len(matrix[a])):
                print(str(round(matrix[a][b], 3)).ljust(5), end='\t')
            print('\n', end='')
        print('\n', end='')

    
    print('Исходная матрица:')
    printMatrix(matrix)

    coefficients = [matrix[i][i] for i in range(size)]
    for i in range(size):
        for j in range(size):
            matrix[i][j] /= (-coefficients[i])
            if i == j:
                matrix[i][j] = 0
        matrix[i][size] /= (coefficients[i])
    x_prev = [matrix[i][-1] for i in range(size)]
    x_next = [0]*size

if __name__ == '__main__':
    matrix = []
    eps = 0.001
    with open('zeidel.txt', 'r') as f:
        for line in f:
            matrix.append([float(i) for i in line.split()])
    zeidel(matrix, eps)