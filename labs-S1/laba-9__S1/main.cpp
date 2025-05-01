/*
Вариант 9.
Дано целое число типа int, выведите на экран содержимое каждого из его байтов,
 используя знания по указателям. Дайте обоснование полученному результату.
*/

#include <iostream>
using namespace std;

int main() {
    int number;
    cout << "Введите целое число: ";
    cin >> number;

    // Указатель на int
    int* ptr = &number;

    // Преобразуем указатель на int в указатель на unsigned char
    unsigned char* bytePtr = reinterpret_cast<unsigned char*>(ptr);

    cout << "Содержимое каждого байта переменной " << number << ": \n";
    for (size_t i = 0; i < sizeof(int); ++i) {
        cout << "Байт " << i << ": " << static_cast<int>(bytePtr[i]) << "\n";
    }

    return 0;
}
