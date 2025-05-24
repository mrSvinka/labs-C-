//----------------МИП-МИП------------------
#include "map.h"

std::vector<sf::FloatRect> holes; 

void initMap() 
{
    // Инициализация дыр (пней) на карте
    holes.emplace_back(3, 17, 1, 1);   
    holes.emplace_back(0, 4, 0.5, 1);
    holes.emplace_back(11.5, 4, 1, 1); 
    holes.emplace_back(16.5, 20, 1, 1);
}

// Проверка позиции на пересечение с дырами
bool isPositionInHole(sf::Vector2f pos) 
{
    for (auto& hole : holes) 
    {
        if (hole.contains(pos)) return true;
    }
    return false;
}