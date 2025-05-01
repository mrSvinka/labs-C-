#include <iostream>
#include <limits>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;
/*
Вариант 9.
Написать программу, которая рассчитает площадь треугольника по известному углу a,
 сторонам A и B. Считается, что треугольник существует.

        А - сторона
        В - сторона
        а - угол
        S - площадь
                         S = (a * b * sinα) / 2 - фрмуля
                        треугольник заведомо существует*
*/

double calculateArea(double A, double B, double radians) //формула.
{
    double area = A * B * sin(radians)*0.5;
    return area;
}

double degrees_to_radians(double degrees)   //приобразует градусы в радианы.
{
    return degrees * M_PI / 180.0;
}

int main()  //созд. перемен. Получает и сохран. данные.
{
    double A;
    std::cout << "side A: ";
    std::cin >> A;

    double B;
    std::cout << "side B: ";
    std::cin >> B;

    double degrees;
    std::cout << "corner: ";
    std::cin >> degrees;
    double radians = degrees_to_radians(degrees); //радианы.
    
    std::cout << "Square: " << calculateArea(A, B, radians) << std::endl; //вывод данных.
    
    return 0;
}
