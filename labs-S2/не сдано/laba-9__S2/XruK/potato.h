//-------------------КАРТОФЛЯ-----------------------
#ifndef POTATO_H
#define POTATO_H

#include <SFML/Graphics.hpp>

class Potato 
{
public:
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;
    float timer;
    float directionChangeTime;

    Potato();
    void respawn();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    void randomizeDirection();
    float clamp(float value, float min, float max);
};

#endif