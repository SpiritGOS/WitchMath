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
    new_matrix = [[matrix[i][j] for j in range(size + 1)] for i in range(size)]
    for i in range(size):
        for j in range(size):
            new_matrix[i][j] /= (-coefficients[i])
            if i == j:
                new_matrix[i][j] = 0
        new_matrix[i][size] /= (coefficients[i])
    x_prev = [new_matrix[i][-1] for i in range(size)]
    x_next = [0]*size

    for i in range(size):
        for j in range(i):
            x_next[i] += new_matrix[i][j]*x_next[j]
        for j in range(i, size):
            x_next[i] += new_matrix[i][j]*x_prev[j]
        x_next[i] += new_matrix[i][size]
    x = 0
    for i in range(size):
        x += matrix[0][i]*x_next[j]
    print(x)
    

if __name__ == '__main__':
    matrix = []
    eps = 0.001
    with open('zeidel.txt', 'r') as f:
        for line in f:
            matrix.append([float(i) for i in line.split()])
    zeidel(matrix, eps)