/*Лабораторная работа №6
“Шаблоны и матрица”

Реализуйте шаблонный класс для описания матриц (в частном случае, векторов). Предусмотрите 3 шаблонных параметра: тип элемента, размеры матрицы N и M (N, M <= 3)
     	В составе класса должны быть:
Базовый конструктор
Конструктор копирования
Оператор присваивания копированием
Оператор ввода и вывода
Операторы +, +=, *, *=
Оператор ++, который увеличивает все элементы матрицы на 1
Метод вычисления определителя
Метод или оператор для получения и изменения элемента матрицы по индексу
 
Продемонстрируйте работу с классом.
*/

#include <iostream>
#include <array>
#include <stdexcept>

template<typename T, size_t N, size_t M>
class Matrix {
    static_assert(N <= 3 && M <= 3, "Matrix dimensions must be <= 3x3");
    
    std::array<std::array<T, M>, N> data;

public:


    // Базовый конструктор
    Matrix() 
	{ 
        for(auto& row : data) row.fill(T());
    }


    // Конструктор копирования
    Matrix(const Matrix& other) = default;


    // Оператор присваивания
    Matrix& operator=(const Matrix& other) = default;


    // Оператор ввода
    friend std::istream& operator>>(std::istream& is, Matrix& m) 
	{
        for(size_t i = 0; i < N; ++i)
            for(size_t j = 0; j < M; ++j)
                is >> m.data[i][j];
        return is;
    }


    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) 
	{
        for(size_t i = 0; i < N; ++i) 
		{
            for(size_t j = 0; j < M; ++j)
                os << m.data[i][j] << ' ';
            os << '\n';
        }
        return os;
    }


    // Оператор +
    Matrix operator+(const Matrix& rhs) const 
	{
        Matrix res;
        for(size_t i = 0; i < N; ++i)
            for(size_t j = 0; j < M; ++j)
                res.data[i][j] = data[i][j] + rhs.data[i][j];
        return res;
    }


    // Оператор +=
    Matrix& operator+=(const Matrix& rhs) 
	{
        return *this = *this + rhs;
    }


    // Оператор * (матричное умножение)
    template<size_t K>
    Matrix<T, N, K> operator*(const Matrix<T, M, K>& rhs) const 
	{
        Matrix<T, N, K> res;
        for(size_t i = 0; i < N; ++i)
            for(size_t j = 0; j < K; ++j)
                for(size_t k = 0; k < M; ++k)
                    res(i,j) += data[i][k] * rhs(k,j);
        return res;
    }


    // Оператор *= (только для квадратных матриц)
    Matrix& operator*=(const Matrix& rhs) 
	{
        static_assert(N == M, "*= only for square matrices");
        return *this = *this * rhs;
    }


    // Префиксный ++
    Matrix& operator++() 
	{
        for(auto& row : data)
            for(auto& val : row)
                ++val;
        return *this;
    }


    // Постфиксный ++
    Matrix operator++(int) 
	{
        Matrix tmp = *this;
        ++*this;
        return tmp;
    }


    // Определитель
    T determinant() const 
	{
        static_assert(N == M, "Determinant only for square matrices");
        
        if constexpr(N == 1) return data[0][0];
        else if constexpr(N == 2)
            return data[0][0]*data[1][1] - data[0][1]*data[1][0];
        else if constexpr(N == 3)
            return data[0][0]*(data[1][1]*data[2][2] - data[1][2]*data[2][1]) -
                   data[0][1]*(data[1][0]*data[2][2] - data[1][2]*data[2][0]) +
                   data[0][2]*(data[1][0]*data[2][1] - data[1][1]*data[2][0]);
        return T();
    }


    // Доступ к элементам
    T& operator()(size_t i, size_t j) 
	{
        if(i >= N || j >= M) throw std::out_of_range("Matrix indices out of range");
        return data[i][j];
    }

    const T& operator()(size_t i, size_t j) const 
	{
        if(i >= N || j >= M) throw std::out_of_range("Matrix indices out of range");
        return data[i][j];
    }
};





int main() 
{
    // Демонстрация работы с матрицами
    Matrix<int, 2, 2> m1;
    std::cout << "Enter 2x2 matrix:\n";
    std::cin >> m1;

    Matrix<int, 2, 2> m2;
    std::cout << "Enter another 2x2 matrix:\n";
    std::cin >> m2;

    auto sum = m1 + m2;
    std::cout << "\nSum:\n" << sum;

    auto prod = m1 * m2;
    std::cout << "\nProduct:\n" << prod;

    std::cout << "\nDeterminant of m1: " << m1.determinant();
    std::cout << "\nDeterminant of m2: " << m2.determinant();

    ++m1;
    std::cout << "\n\nAfter increment:\n" << m1;

    // Вектор-столбец
    Matrix<double, 3, 1> vec;
    vec(0,0) = 1.5;
    vec(1,0) = 2.3;
    vec(2,0) = 3.1;
    std::cout << "\nVector:\n" << vec;

    return 0;
}