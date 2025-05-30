//---------------------------ПОЛНАЯ КАРТОФЛЯ------------------------------
#include "potato.h"
#include "map.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

// загрузка текстуры, начальная позиция
Potato::Potato() : speed(6.0f), directionChangeTime(2.0f), timer(directionChangeTime) 
{
    if (!texture.loadFromFile("Textures/potato.png")) 
    {
        std::cerr << "ERROR: Failed to load potato.png!" << std::endl;
        exit(1);
    }
    sprite.setTexture(texture);
    
// Масштабирование спрайта под размер клетки
float scaleX = (CELL_SIZE * 1) / static_cast<float>(texture.getSize().x);
float scaleY = (CELL_SIZE * 1) / static_cast<float>(texture.getSize().y);
    sprite.setScale(scaleX, scaleY);
    
    respawn(); // Начало
}
 // Респаун картофана
void Potato::respawn() 
{
    do 
    {
        position = sf::Vector2f(rand() % GRID_SIZE, rand() % GRID_SIZE);
    } 
    while (isPositionInHole(position));
    randomizeDirection(); // Новое направление
}

// Обновление позиции картошки
void Potato::update(float deltaTime) 
{
    timer -= deltaTime;
    if (timer <= 0)  // Смена направления по таймеру
    {
        randomizeDirection();
        timer = directionChangeTime;
    }

    // Расчет новой позиции
    sf::Vector2f newPos = position + direction * speed * deltaTime;
    newPos.x = clamp(newPos.x, 0.0f, static_cast<float>(GRID_SIZE - 1));
    newPos.y = clamp(newPos.y, 0.0f, static_cast<float>(GRID_SIZE - 1));

    // Проверка коллизии с пнями
    if (!isPositionInHole(newPos)) 
    {
        position = newPos;
    } 
    else 
    {
        randomizeDirection(); // Смена направления при
    }
}

// Отрисовка спрайта картофана
void Potato::draw(sf::RenderWindow& window) 
{
    sprite.setPosition(position.x * CELL_SIZE, position.y * CELL_SIZE);
    window.draw(sprite);
}

// Генерация случайного направления
void Potato::randomizeDirection() 
{
    direction = sf::Vector2f(
        (rand() % 200 - 100) / 100.0f, // Случайные значения
        (rand() % 200 - 100) / 100.0f
    );
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) direction /= length;
}

// Ограничение значения в диапазон
float Potato::clamp(float value, float min, float max) 
{
    return std::max(min, std::min(value, max));
}