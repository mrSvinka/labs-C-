/*Лабораторная работа №8
“Графические примитивы”

Подключите к проекту библиотеку SFML (любой версии):
Используйте официальную документацию Tutorials - Simple and Fast Multimedia Library;
Либо готовые репозитории mrBelka/sfml_sample (v. 2.5.1), mrBelka/sfml_sample_3_0 (v. 3.0);

	Выведите на экран 3 произвольный фигуры (круг, квадрат, прямоугольник, линию, полигон и т.п.).

	Измените цвет, положение и угол поворота фигур.
*/


#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    // Создание окна
    RenderWindow window(VideoMode(800, 600),"");

    // Создание фигур
    // 1. Круг 
    CircleShape circle(50);
    circle.setFillColor(Color::Red);
    circle.setPosition(411, 51);
    circle.setRotation(46);

    // 2. Прямоугольник
    RectangleShape rectangle(Vector2f(170, 288));
    rectangle.setFillColor(Color::Green);
    rectangle.setPosition(333, 222);
    rectangle.setRotation(-30);

    // 3. Треугольник 
    ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, Vector2f(23, 5));
    triangle.setPoint(1, Vector2f(198, 4));
    triangle.setPoint(2, Vector2f(54, 101));
    triangle.setFillColor(Color::Blue);
    triangle.setPosition(566, 433);
    triangle.setRotation(15);


    // Основная часть
    while (window.isOpen())
    {
        // Обработка 
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Очистка экрана
        window.clear(Color::White);

        // Отрисовка фигур
        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);

        // Обновление окна
        window.display();
    }

    return 0;
}