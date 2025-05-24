//----------------МИП-МИП------------------
#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

extern std::vector<sf::FloatRect> holes; // пни на карте
const int GRID_SIZE = 16+8;
const int CELL_SIZE = 30+15;
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE; // Размер окна

// Функции:
void initMap(); // Инициализация дыр на карте
bool isPositionInHole(sf::Vector2f pos); // Проверка позиции на попадание в дыру

#endif