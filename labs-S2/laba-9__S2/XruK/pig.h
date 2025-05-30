//-----------------------ПИГНЯ------------------------
#ifndef PIG_H
#define PIG_H

#include <SFML/Graphics.hpp>

class Pig 
{
public:
    sf::Vector2f position; // Текущая позиция
    float speed; // Скорость движения
    
    Pig();
    void update(float deltaTime); // Обновление позиции
    void draw(sf::RenderWindow& window); // Отрисовка

private:
    sf::Texture texture; // Текстура хрюндиля
    sf::Sprite sprite; // отрисовка
    float clamp(float value, float min, float max);
};

#endif