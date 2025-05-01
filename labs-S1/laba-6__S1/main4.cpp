
//4.   Сначала введите последовательность. Затем удалите и продублируйте элементы. 
//     Затем выведите полученную последовательность (каждый элемент по одному разу).
//     Используйте в программе только один массив.


#include <iostream>
using namespace std;

const int MAX_SIZE = 100; 
int main() 
{
    int n, a[MAX_SIZE];

    // Ввод 
    cout << "введите длину последовательности (n<=100): ";
    cin >> n;

    if (n <= 0 || n > MAX_SIZE) 
    {
        cerr << "некорректная длина последовательности" << endl;
        return 1;
    }

    cout << "введите последовательность: ";
    for (int i = 0; i < n; i++) 
    {
        cin >> a[i];
    }

    // Удаление и дублирование 
    for (int i = 0; i < n; i++) 
    {
        int temp = a[i];
        for (int j = i; j < n - 1; j++) 
        {
            a[j] = a[j + 1];
        }
        a[n - 1] = temp;
        i++;
        for (int j = n - 1; j > i; j--) 
        {
            a[j] = a[j - 1];
        }
        a[i] = temp;
        n++;
    }

    // Удаление 
    for (int i = 0; i < n; i++) 
    {
        for (int j = i + 1; j < n;) 
        {
            if (a[j] == a[i]) 
            {
                for (int k = j; k < n - 1; k++) 
                {
                    a[k] = a[k + 1];
                }
                n--;
            } else 
            {
                j++;
            }
        }
    }

    // Вывод 
    cout << "последовательность: ";
    for (int i = 0; i < n; i++) 
    {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}
