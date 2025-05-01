#ifndef MATRIX_OPERATIONS_HPP
#define MATRIX_OPERATIONS_HPP

const int MAX_SIZE = 100;

namespace MatrixOps 
{
    void readMatrix(int matrix[MAX_SIZE][MAX_SIZE], int& n);
    void processMatrix(int matrix[MAX_SIZE][MAX_SIZE], int n);
    void writeMatrix(int matrix[MAX_SIZE][MAX_SIZE], int n);
    bool containsDigitEight(int number);
}

#endif // MATRIX_OPERATIONS_HPP
