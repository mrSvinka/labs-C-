/*
Вариант: 9.
Вывести значение i-го бита числа x (0<x<10^9).
*/

#include <iostream>

int main()
{
    unsigned int x;
    std::cout << "Enter number: "; //получили число
    std::cin >> x;

    int i;
    std::cout << "Select number: "; //получили число
    std::cin >> i;


    int bitValue = (x >> i) & 1; //получаем значения бита

    std::cout << " Bit value: " << bitValue << std::endl; //выводим значение

    return 0;
}











