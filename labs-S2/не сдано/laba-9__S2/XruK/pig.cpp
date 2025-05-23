//----------------------------ПОЛНАЯ ПИГНЯ------------------------
#include "pig.h"
#include "map.h"
#include <cmath>
#include <iostream>

Pig::Pig() {
    if (!texture.loadFromFile("Textures/pig.png")) {
        std::cerr << "ERROR: Failed to load pig.png!" << std::endl;
        exit(1);
    }
    sprite.setTexture(texture);
    
float scaleX = (CELL_SIZE * 3) / static_cast<float>(texture.getSize().x);
float scaleY = (CELL_SIZE * 2) / static_cast<float>(texture.getSize().y);
    sprite.setScale(scaleX, scaleY);
    
    do {
        position = sf::Vector2f(rand() % GRID_SIZE, rand() % GRID_SIZE);
    } while (isPositionInHole(position));
    
    speed = 5.0f;
}

void Pig::update(float deltaTime) {
    sf::Vector2f movement(0, 0);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += 1;

    if (movement.x != 0 || movement.y != 0) {
        float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        movement /= length;
    }

    sf::Vector2f newPos = position + movement * speed * deltaTime;
    newPos.x = clamp(newPos.x, 0.0f, static_cast<float>(GRID_SIZE - 1));
    newPos.y = clamp(newPos.y, 0.0f, static_cast<float>(GRID_SIZE - 1));

    if (!isPositionInHole(newPos)) {
        position = newPos;
    }
}

void Pig::draw(sf::RenderWindow& window) {
    sprite.setPosition(position.x * CELL_SIZE, position.y * CELL_SIZE);
    window.draw(sprite);
}

float Pig::clamp(float value, float min, float max) {
    return std::max(min, std::min(value, max));
}