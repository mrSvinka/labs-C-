/*
Дано натуральной число N (N<2^31), определите, сколько в нем цифр с использованием рекурсии.
*/


#include <iostream>
using namespace std;

int count_chis(int n) 
{
    if (n < 10) return 1;
    return 1 + count_chis(n / 10);
}

int main() 
{
    int N;
    cout << "Число N: ";
    cin >> N;
    cout << "Количество цифр: " << count_chis(N) << endl;
    return 0;
}


