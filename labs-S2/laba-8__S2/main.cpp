/*Лабораторная работа №8
“Графические примитивы”

Подключите к проекту библиотеку SFML (любой версии):
Используйте официальную документацию Tutorials - Simple and Fast Multimedia Library;
Либо готовые репозитории mrBelka/sfml_sample (v. 2.5.1), mrBelka/sfml_sample_3_0 (v. 3.0);

	Выведите на экран 3 произвольный фигуры (круг, квадрат, прямоугольник, линию, полигон и т.п.).

	Измените цвет, положение и угол поворота фигур.
*/


#include <SFML/Graphics.hpp>

int main()
{
    // Создание окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "Графические примитивы");

    // Создание фигур
    // 1. Круг (радиус 50, красный)
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(100, 100);
    circle.setRotation(45); // Поворот на 45 градусов

    // 2. Прямоугольник (100x200, зелёный)
    sf::RectangleShape rectangle(sf::Vector2f(100, 200));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(400, 200);
    rectangle.setRotation(-30); // Поворот на -30 градусов

    // 3. Треугольник (синий)
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0, 0));
    triangle.setPoint(1, sf::Vector2f(100, 0));
    triangle.setPoint(2, sf::Vector2f(50, 100));
    triangle.setFillColor(sf::Color::Blue);
    triangle.setPosition(600, 400);
    triangle.setRotation(15); // Поворот на 15 градусов

    // Главный цикл приложения
    while (window.isOpen())
    {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Очистка экрана
        window.clear(sf::Color::White);

        // Отрисовка фигур
        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);

        // Обновление окна
        window.display();
    }

    return 0;
}