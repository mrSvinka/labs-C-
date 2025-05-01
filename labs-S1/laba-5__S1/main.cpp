/*
Вариант 9
Дана последовательность целых чисел {Aj}. Найти произведение чисел, оканчивающихся цифрой 2, наибольшее из таких чисел и номер этого числа в последовательности.

Дано натуральное число N (N<10^9). Найти наиболее часто встречающуюся цифру числа N. Если таких чисел несколько, выведите любое.
*/


#include <iostream>
#include <vector>
#include <map>
using namespace std;





int main() 
{
//последовательнасть
    int n;
    cout << "Enter subsequence: "; //получили послед.
    cin >> n;

    long long product = 1;
    int maxNum = 0;
    int maxIndex = 0;



for (int i = 1; i <= n; ++i) 
{
        int num;
        cout << "Введите число " << i << ": ";
        cin >> num;
//оканчивается ли число на 2?
        if (num % 10 == 2) 
        {
            product *= num;
// проверка на максимальное число
            if (num > maxNum) 
            {
                maxNum = num;  //число
                maxIndex = i; // номер (индекс + 1)
            }
        }
    }

    if (maxNum == 0) 
    {
        cout << "нет чисела, оканчивающивося на 2." << endl;
    } 
    else 
    {
        cout << "произведение чисел, оканчивающихся на 2: " << product << endl;
        cout << "наибольшее число, оканчивающееся на 2: " << maxNum << endl;
        cout << "номер числа в последовательности: " << maxIndex << endl;
    }

//Найти наиболее часто встречающуюся цифру числа N
    long long N;
    cout << "Enter N (N < 10^9): ";
    cin >> N;

    map<int, int> Count;
    while (N > 0) 
    {
        int digit = N % 10;
       Count[digit]++;
        N /= 10;
    }

    int maxCount = 0;
    int most_frequent_digit = -1;

    for (const auto& pair : Count) 
    {
        if (pair.second > maxCount) 
        {
            maxCount = pair.second;
            most_frequent_digit = pair.first;
        }
    }

    cout << "наиболее часто встречающуюся цифру числа N: " << most_frequent_digit << endl;

    return 0;
}
