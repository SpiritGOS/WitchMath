from math import atan, cos, sin

def rotation_method(matrix, eps):
    rotated = [[1 if row == col else 0 for row in range(len(matrix))] for col in range(len(matrix))]
    return rotations(matrix, rotated, eps)

def rotations(matrix, rotated_matrix, eps):
    def printMatrix(matrix):
        for a in range(len(matrix)):
            for b in range(len(matrix[a])):
                print(str(round(matrix[a][b], 3)).ljust(5), end='\t')
            print('\n', end='')
        print('\n', end='')
    
    def transpon(matrix):
        n = len(matrix)
        transpon_matrix = []
        for i in range(n):
            transpon_matrix.append([0]*n)
        for i in range(n):
            for j in range(n):
                transpon_matrix[i][j] = matrix[j][i]
        return(transpon_matrix)
    
    def multiply_matrix(A, B):
        length = len(A) 
        result_matrix = [[0.0 for i in range(length)] for i in range(length)]
        for i in range(length):
            for j in range(length):
                for k in range(length):
                    result_matrix[i][j] += A[i][k] * B[k][j]
        return result_matrix
    
    def final():
        size = len(rotated_matrix)
        lambdas = []
        for i in range(size):
            for j in range(size):
                if i == j:
                    lambdas.append(matrix[i][j])
        V = rotated_matrix
        return (lambdas, V)

    if eps >= 1:
       return final()

    print('Исходная матрица:')
    printMatrix(matrix)
    size = len(matrix)
    max_ = 0

    
    for i in range(size):
        for j in range(i,size):
            if i == j:
                pass
            elif abs(matrix[i][j]) >= max_:
                max_ = abs(matrix[i][j])
                k = i  # maxi по методе
                m = j  # maxj по методе

    try:
        phi = 0.5 * atan((2 * matrix[k][m]) /
                            (matrix[k][k] - matrix[m][m]))
    except ZeroDivisionError:
        if matrix[k][m] >= 0:
            phi = -0.78539816339
        else:
            phi = 0.78539816339

    h_kk = cos(phi)
    h_mk = sin(phi)
    h_km = -sin(phi)
    h_mm = cos(phi)

    E = [[1 if i == j else 0 for i in range(size)] for j in range(size)]
        
        
    H = E
    H[k][k] = h_kk
    H[m][k] = h_mk  
    H[k][m] = h_km
    H[m][m] = h_mm
    Ht = transpon(H)
    matrix_1 = multiply_matrix(Ht, multiply_matrix(matrix, H))
    return rotations(matrix_1, multiply_matrix(rotated_matrix, H), eps*10)


if __name__ == '__main__':
    matrix = []
    eps = 0.0000001
    with open('C:\\Users\\marse\\OneDrive\\Документы\\Проекты\\Вычислительная математика\\First Wave\\Rotations\\Matrix.txt', 'r') as f:
        for line in f:
            matrix.append([float(i) for i in line.split()])
    # A = np.matrix(matrix)
    # print(type(A))
    # print(A)
    rotated = [[1 if row == col else 0 for row in range(len(matrix))] for col in range(len(matrix))]
    lambdas, V = rotation_method(matrix, eps)
    [print(f'lambda[{i + 1}] = {l}') for i, l in enumerate(lambdas)]
    [print(f'x[{i + 1}] = {l}') for i, l in enumerate(V)]