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
using namespace std;


// Matrix
template<typename T, size_t N, size_t M>
class Matrix 
{
    //  максимальный размер матрицы 
    static_assert(N <= 3 && M <= 3, "Размеры матрицы должны быть <= 3x3");
     // Хранение данных в виде двумерного массива
    array<array<T, M>, N> data;

public:


    // Базовый конструктор (инициализирует все элементы значением по умолчанию для T)
    Matrix() 
	{ 
        for(auto& row : data) row.fill(T());
    }


    // Конструктор копирования
    Matrix(const Matrix& other) = default;


    // Оператор присваивания копированием
    Matrix& operator=(const Matrix& other) = default;


    // Оператор ввода
    friend istream& operator>>(istream& is, Matrix& m) 
	{
        for(size_t i = 0; i < N; ++i)
            for(size_t j = 0; j < M; ++j)
                is >> m.data[i][j];
        return is;
    }


    // Оператор вывода
    friend ostream& operator<<(ostream& os, const Matrix& m) 
	{
        for(size_t i = 0; i < N; ++i) 
		{
            for(size_t j = 0; j < M; ++j)
                os << m.data[i][j] << ' '; // Поэлементный вывод
            os << '\n'; // Переход на новую строку после каждой строки матрицы
        }
        return os;
    }


    // Оператор сложения матриц
    Matrix operator+(const Matrix& rhs) const 
	{
        Matrix res;
        for(size_t i = 0; i < N; ++i)
            for(size_t j = 0; j < M; ++j)
                res.data[i][j] = data[i][j] + rhs.data[i][j]; // Поэлементное сложение
        return res;
    }


    // сложение с присваиванием
    Matrix& operator+=(const Matrix& rhs) 
	{
        return *this = *this + rhs; // Оператор сложения матриц
    }


    // Оператор умножения матриц 
    template<size_t K>
    Matrix<T, N, K> operator*(const Matrix<T, M, K>& rhs) const 
	{
        Matrix<T, N, K> res;
        for(size_t i = 0; i < N; ++i)
            for(size_t j = 0; j < K; ++j)
                for(size_t k = 0; k < M; ++k)
                    res(i,j) += data[i][k] * rhs(k,j); // Формула матричного умножения
        return res;
    }















    




// Умножение с присваиванием:   (N×M) *=  (M×M)  результат: (N×M)
Matrix& operator*=(const Matrix<T, M, M>& rhs) 
{
    static_assert(M > 0);
    *this = *this * rhs; // Используем оператор *
    return *this;
}


    // Префиксный ++
    Matrix& operator++() 
	{
        for(auto& row : data)
            for(auto& val : row)
                ++val; // Увеличивает каждый элемент на 1
        return *this;
    }


    // Постфиксный ++
    Matrix operator++(int) 
	{
        Matrix tmp = *this; // Сохраняет текущее состояние
        ++*this; // Применяет префиксный инкремент
        return tmp; // Возвращает старое состояние
    }


     // Метод вычисления определителя 
    T determinant() const 
	{
        static_assert(N == M);
        
        // Формулы для матриц 1x1 - 3x3
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
        if(i >= N || j >= M) throw out_of_range("Индексы матрицы выходят за пределы диапазона");
        return data[i][j];
    }

    const T& operator()(size_t i, size_t j) const 
	{
        if(i >= N || j >= M) throw out_of_range("Индексы матрицы выходят за пределы диапазона");
        return data[i][j];
    }
};





int main() 
{
    // пример
    Matrix<int, 2, 2> m1;
    cout << "Введите матрицу 2x2:\n";
    cin >> m1;

    Matrix<int, 2, 2> m2;
    cout << "Введите еще одну матрицу 2x2:\n";
    cin >> m2;

    auto sum = m1 + m2;
    cout << "\nСумма:\n" << sum;

    auto prod = m1 * m2;
    cout << "\nПродукт:\n" << prod;

    cout << "\nОпределитель m1: " << m1.determinant();
    cout << "\nОпределитель m2:: " << m2.determinant();

    ++m1;
    cout << "\n\nПосле приращения:\n" << m1;

    // Вектор-столбец
    Matrix<double, 3, 1> vec;
    vec(0,0) = 1.5;
    vec(1,0) = 2.3;
    vec(2,0) = 3.1;
    cout << "\nVector:\n" << vec;

    return 0;
}