//-----------------------ПИГНЯ------------------------
#ifndef PIG_H
#define PIG_H

#include <SFML/Graphics.hpp>

class Pig {
public:
    sf::Vector2f position;
    float speed;
    
    Pig();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    float clamp(float value, float min, float max);
};

#endif