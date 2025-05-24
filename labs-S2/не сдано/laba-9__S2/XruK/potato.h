//-------------------КАРТОФЛЯ-----------------------
#ifndef POTATO_H
#define POTATO_H

#include <SFML/Graphics.hpp>

class Potato 
{
public:
    sf::Vector2f position; // Текущая позиция
    sf::Vector2f direction; // Направление движения
    float speed; // Скорость движения
    float timer; // Таймер до смены направления
    float directionChangeTime; // Интервал смены направления 

    Potato();
    void respawn(); // Перемещение картошки
    void update(float deltaTime); // Обновление позиции
    void draw(sf::RenderWindow& window); // Отрисовка

private:
    sf::Texture texture;
    sf::Sprite sprite;
    void randomizeDirection(); // Случайное изменение направления
    float clamp(float value, float min, float max); // Ограничение значения
};

#endif