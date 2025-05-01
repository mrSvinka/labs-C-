//3. 	Дана целочисленная матрица {Aij}i=1..n,j=1..m (n,m<=100). Найти строку, в которой меньше всего четных чисел, и заменить все элементы этой строки их квадратами.

#include <iostream>
using namespace std;

int main() 
{
    int n, m;
    cout << "Введите количество строк: ";
    cin >> n;
    cout << "Введите количество столбцов: ";
    cin >> m;


    int A[n][m]; 

    // Ввод 
    cout << "Введите элементы матрицы: " << endl;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            cin >> A[i][j];
        }
    }

    int min_count = m + 1; // Максимально возможное количество четных чисел
    int min_row = -1; // Индекс строки с минимальным количеством четных

    // Поиск строки с наименьшим количеством четных чисел
    for (int i = 0; i < n; i++) 
    {
        int evenCount = 0;
        for (int j = 0; j < m; j++) 
        {
            if (A[i][j] % 2 == 0) 
            {
                evenCount++;
            }
        }
        if (evenCount < min_count) 
        {
            min_count = evenCount;
            min_row = i;
        }
    }

    // Заменяем элементы найденной строки на их квадраты
    if (min_row != -1) 
    {
        for (int j = 0; j < m; j++) 
        {
            A[min_row][j] = A[min_row][j] * A[min_row][j];
        }
    }

    // Вывод 
    cout << "Измененная матрица: " << endl;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
