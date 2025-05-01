
/*2. 	Ввести последовательность натуральных чисел {Aj}j=1...n (n<=1000). Упорядочить последовательность по неубыванию произведения цифр числа, 
числа с одинаковыми произведениями цифр дополнительно упорядочить по неубыванию первой цифры числа, 
числа с одинаковыми произведениями цифр и одинаковыми первыми цифрами дополнительно упорядочить по неубыванию самого числа.
*/


#include <iostream>
#include <algorithm>
using namespace std;

// Произведение цифр числа
int product_ch(int number) 
{
    int product = 1;
    number = abs(number);
    while (number > 0) 
    {
        product *= number % 10;
        number /= 10;
    }
    return product;
}

// Первая цифра числа
int first(int number) 
{
    number = abs(number);
    while (number >= 10) 
    {
        number /= 10;
    }
    return number;
}

// Компаратор для сортировки
bool compare(int a, int b) 
{
    int prodA = product_ch(a);
    int prodB = product_ch(b);
    
    if (prodA == prodB) 
    {
        int firstA = first(a);
        int firstB = first(b);
        
        if (firstA == firstB) 
        {
            return a < b;  // Сравнение самих чисел
        }
        return firstA < firstB;  // Сравнение по первой цифре
    }
    return prodA < prodB;  // Сравнение по произведению
}

// Ввод
int main() 
{
    const int MAX_N = 10000;
    int numbers[MAX_N]; 

    int n;
    cout << "Введите количество чисел: ";
    cin >> n;

    for (int i = 0; i < n; ++i) 
    {
        cout << "Введите число " << (i + 1) << ": ";
        cin >> numbers[i];
    }

    // Сортировка
    sort(numbers, numbers + n, compare);

    // Вывод 
    cout << "Последовательность: " << endl;
    for (int i = 0; i < n; i++) 
    {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}

