//    Дана последовательность натуральных чисел {Aj}j=1...n (n<=10000). Удалить из последовательности числа,
//    произведение цифр которых равно 180, а среди оставшихся продублировать числа, начинающиеся и заканчивающиеся цифрой 1.


#include <iostream>
using namespace std;



int prod(int num) 
{
    int product = 1;
    while (num > 0) 
    {
        product *= num % 10;
        num /= 10;
    }
    return product;
}

bool Ah(int num) 
{
    return (num / 10 == 1 && num % 10 == 1);
}

int main() 
{
    const int MAX_SIZE = 10000;
    int A[MAX_SIZE];
    int n;
//ввод
    cout << "Введите количество чисел (n<=10000): ";
    cin >> n;

    cout << "Введите числа: " << "  ";
    for (int i = 0; i < n; i++) 
    {
        cin >> A[i];
    }

    int result[MAX_SIZE * 2]; // для хранения результата
    int index = 0;

    for (int i = 0; i < n; i++) 
    {
        if (prod(A[i]) != 180) 
        {
            result[index++] = A[i]; // число не удаляется
            if (Ah(A[i])) 
            {
                result[index++] = A[i]; // Дублирование числа
            }
        }
    }

    //вывод
    cout << "Результат: " << endl;
    for (int i = 0; i < index; i++) 
    {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
