#include <iostream>
#include "MatrixOperations.hpp"

#include <iostream>
#include "MatrixOperations.hpp"

namespace MatrixOps 
{
    void readMatrix(int matrix[MAX_SIZE][MAX_SIZE], int& n) 
    {
        std::cout << "Введите размер матрицы n (<= 100): ";
        std::cin >> n;
        std::cout << "Введите элементы матрицы:\n";
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                std::cin >> matrix[i][j];
    }

    bool containsDigitEight(int number) 
    {
        return std::to_string(number).find('8') != std::string::npos;
    }

    void sortRow(int row[], int n) 
    {
        for (int i = 0; i < n - 1; ++i)
            for (int j = i + 1; j < n; ++j)
                if (row[i] > row[j])
                    std::swap(row[i], row[j]);
    }

    void processMatrix(int matrix[MAX_SIZE][MAX_SIZE], int n) 
    {
        int maxElement = matrix[0][0];
        int minElement = matrix[0][0];

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) 
            {
                if (matrix[i][j] > maxElement) maxElement = matrix[i][j];
                if (matrix[i][j] < minElement) minElement = matrix[i][j];
            }

        if (maxElement + minElement == 0) 
        {
            for (int i = 0; i < n; ++i) 
            {
                bool hasEight = false;
                for (int j = 0; j < n; ++j) 
                {
                    if (containsDigitEight(matrix[i][j])) 
                    {
                        hasEight = true;
                        break;
                    }
                }
                if (hasEight) 
                {
                    sortRow(matrix[i], n); 
                }
            }
        }
    }

    void writeMatrix(int matrix[MAX_SIZE][MAX_SIZE], int n) 
    {
        std::cout << "Упорядоченная матрица:\n";
        for (int i = 0; i < n; ++i) 
        {
            for (int j = 0; j < n; ++j)
                std::cout << matrix[i][j] << " ";
            std::cout << "\n";
        }
    }
}

