/*
Реализуйте быструю сортировку. Изучите, как она работает. Сравните скорость работы с сортировкой обменами.
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void quickSort(int a[], int left, int right) 
{
    if (left >= right) return;    // если все хорошо
    int pivot = a[(left + right) / 2];   // Выбор опорного элемента
    int i = left, j = right;    //  указатели (создание)
    while (i <= j) 
    {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) swap(a[i++], a[j--]);
    }
    quickSort(a, left, j);
    quickSort(a, i, right);
}

void bubble(int a_c[], int n) 
{
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (a_c[j] > a_c[j+1]) swap(a_c[j], a_c[j+1]);
}

int main() 
{
    //кол-во элементов.
    const int SIZE = 10000;
    int a[SIZE], a_c[SIZE];
    srand(time(0));

//рандомные числа
    for (int i = 0; i < SIZE; i++)
    a[i] = a_c[i] = rand() % 10000;

//тестируем быстрый вариант
    clock_t start = clock();
    quickSort(a, 0, SIZE-1);
    cout << "Быстрая сортировка: " << (clock() - start) * 1000.0 / CLOCKS_PER_SEC << " мс" << endl;

    //тестируем пувырик
    start = clock();
    bubble(a_c, SIZE);
    cout << "Пувырик: " << (clock() - start) * 1000.0 / CLOCKS_PER_SEC << " мс" << endl;

    return 0;
}