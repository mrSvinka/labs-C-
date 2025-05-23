//---------------------------ПОЛНАЯ КАРТОФЛЯ------------------------------
#include "potato.h"
#include "map.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

Potato::Potato() : speed(6.0f), directionChangeTime(2.0f), timer(directionChangeTime) {
    if (!texture.loadFromFile("Textures/potato.png")) {
        std::cerr << "ERROR: Failed to load potato.png!" << std::endl;
        exit(1);
    }
    sprite.setTexture(texture);
    
float scaleX = (CELL_SIZE * 1) / static_cast<float>(texture.getSize().x);
float scaleY = (CELL_SIZE * 1) / static_cast<float>(texture.getSize().y);
    sprite.setScale(scaleX, scaleY);
    
    respawn();
}

void Potato::respawn() {
    do {
        position = sf::Vector2f(rand() % GRID_SIZE, rand() % GRID_SIZE);
    } while (isPositionInHole(position));
    randomizeDirection();
}

void Potato::update(float deltaTime) {
    timer -= deltaTime;
    if (timer <= 0) {
        randomizeDirection();
        timer = directionChangeTime;
    }

    sf::Vector2f newPos = position + direction * speed * deltaTime;
    newPos.x = clamp(newPos.x, 0.0f, static_cast<float>(GRID_SIZE - 1));
    newPos.y = clamp(newPos.y, 0.0f, static_cast<float>(GRID_SIZE - 1));

    if (!isPositionInHole(newPos)) {
        position = newPos;
    } else {
        randomizeDirection();
    }
}

void Potato::draw(sf::RenderWindow& window) {
    sprite.setPosition(position.x * CELL_SIZE, position.y * CELL_SIZE);
    window.draw(sprite);
}

void Potato::randomizeDirection() {
    direction = sf::Vector2f(
        (rand() % 200 - 100) / 100.0f,
        (rand() % 200 - 100) / 100.0f
    );
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) direction /= length;
}

float Potato::clamp(float value, float min, float max) {
    return std::max(min, std::min(value, max));
}