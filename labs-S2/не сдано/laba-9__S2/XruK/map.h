//----------------МИП-МИП------------------
#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

extern std::vector<sf::FloatRect> holes;
const int GRID_SIZE = 16+8;
const int CELL_SIZE = 30+15;
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;

void initMap();
bool isPositionInHole(sf::Vector2f pos);

#endif