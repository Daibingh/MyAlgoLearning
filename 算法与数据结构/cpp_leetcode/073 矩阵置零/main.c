

void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int firstRowHasZero = 0;
    int firstColHasZero = 0;
    for (int i = 0; i < matrixSize; ++i) {
        if (matrix[i][0] == 0) {
            firstColHasZero = 1;
            break;
        }
    }
    for (int j = 0; j < *matrixColSize; ++j) {
        if (matrix[0][j] == 0) {
            firstRowHasZero = 1;
            break;
        }
    }
    for (int i = 1; i < matrixSize; ++i) {
        for (int j = 1; j < *matrixColSize; ++j) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }
    for (int i = 1; i < matrixSize; ++i) {
        if (matrix[i][0] == 0)
            memset(matrix[i], 0, *matrixColSize * sizeof(int));
    }
    for (int j = 1; j < *matrixColSize; ++j) {
        if (matrix[0][j] == 0) {
            for (int i = 1; i < matrixSize; ++i)
                matrix[i][j] = 0;
        }
    }
    if (firstRowHasZero)
        memset(matrix[0], 0, *matrixColSize * sizeof(int));
    if (firstColHasZero) {
        for (int i = 0; i < matrixSize; ++i)
            matrix[i][0] = 0;
    }
}