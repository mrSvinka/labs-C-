/*
Вариант 9

1. 	Дана последовательность натуральных чисел {aj}j=1...n (n<=10000). 
Если в последовательности есть хотя бы одно простое число, упорядочить последовательность по неубыванию.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Функция для проверки, является ли число простым
bool isPrime(int num) 
{
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) 
    {
        if (num % i == 0) return false;
    }
    return true;
}

void bubbleSort(int numbers[], int n) // Функция сортировки пузырьком
{ 
    for (int i = 1; i <= n - 1; ++i) 
    {
        for (int j = 1; j <= n - 1 - i; ++j) 
        {
            if (numbers[j] > numbers[j + 1]) 
            {
                swap(numbers[j], numbers[j + 1]);
            }
        }
    }
}



int main() {
    const int MAX_N = 10000;
    int numbers[MAX_N]; 

    int n;
    cout << "Введите количество чисел: ";
    cin >> n;


    for (int i = 1; i <= n; ++i) 
    {
        cout << "Введите число " << i << ": ";
        cin >> numbers[i];
    }

        bool h = false;
    for (int i = 0; i < n; ++i) 
    {
        if (isPrime(numbers[i])) 
        {
            h = true;
            break; 
        }
    }

    if (h) 
    {
        bubbleSort(numbers, n); // Сортируем, если есть простое число
    }

    // Вывод отсортированной или исходной последовательности
    cout << "Результат: ";
    for (int i = 1; i <= n; ++i) 
    {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}