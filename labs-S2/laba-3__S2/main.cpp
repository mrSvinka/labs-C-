/*В соответствии с данным объектом и задачей создайте класс.Опишите необходимые поля и методы, создайте конструктор.
  Приведите пример использования.
  Эллипс, расчет площади, периметра.
*/

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <cmath>
#include <stdexcept> 
using namespace std;




class Ellipse 
{
private:
    double majorAxis; // Большая полуось (a > 0)
    double minorAxis; // Малая полуось (b > 0, b <= a)

    
    //проверка существования фигуры
    void validateAxes(double a, double b) 
    {
        if (a <= 0 || b <= 0) 
        {
            throw invalid_argument("Полуоси должны быть положительными");
        }
        if (a < b) 
        {
            throw invalid_argument("Большая полуось должен быть >= Малая полуось");
        }
    }





public:
    //1) иницилизация
    Ellipse(double majorAxis, double minorAxis) 
    {
        validateAxes(majorAxis, minorAxis);
        this->majorAxis = majorAxis;
        this->minorAxis = minorAxis;
    }


    //2) генерируем главную ось
    double getMajorAxis() const { return majorAxis; }
    double getMinorAxis() const { return minorAxis; }


    //3) устанавливаем главную ось
    void setMajorAxis(double value) 
    {
        validateAxes(value, minorAxis); //проверяем
        majorAxis = value;
    }


    //4) устанавливаем вторую ось
    void setMinorAxis(double value) 
    {
        validateAxes(majorAxis, value);
        minorAxis = value;
    }






   // площадь эллипса по формуле: S = п * a * b
    double calculateArea() const 
    {
        return M_PI * majorAxis * minorAxis;
    }


    //периметр по формуле Рамануджана.
    //Формула: P ≈ п * (a + b) * [1 + 3h/(10 + √(4 - 3h))], где h = ((a - b)/(a + b))²
    double Perimeter() const 
    {
        double a = majorAxis;
        double b = minorAxis;
        double h = pow((a - b)/(a + b), 2);
        return M_PI * (a + b) * (1 + (3*h)/(10 + sqrt(4 - 3*h)));
    }


    //если a == b => эллипс - окружность
    bool isCircle() const 
    {
        return majorAxis == minorAxis;
    }


    //Вывод информации
    void printInfo() const  
    {
        cout << "Ellipse [a=" << majorAxis 
             << ", b=" << minorAxis 
             << "]\nArea: " << calculateArea()
             << "\nPerimeter: " << Perimeter()
             << (isCircle() ? "\nThis is a circle" : "") 
             << endl;
    }
};



//-----------------Пример использования----------------------
int main() 
{
    try 
    {
        // Создание эллипса
        Ellipse ellipse(10.0, 6.0);
        ellipse.printInfo();
        

        // Изменение параметров
        ellipse.setMajorAxis(11.0);
        ellipse.setMinorAxis(11.0);
        ellipse.printInfo();
       

        // Проверка на окружность
        if (ellipse.isCircle()) 
        {
            cout << "Это окружность" << endl;
        }


    } 
    //ошибка
    catch (const invalid_argument& e) 
    {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
