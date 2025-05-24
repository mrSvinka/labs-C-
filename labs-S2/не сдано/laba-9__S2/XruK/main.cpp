#include <SFML/Graphics.hpp>
#include "pig.h"
#include "potato.h"
#include "map.h"
#include <iostream>

int main() 
{
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "XruK:Нажората");     
    
    // Загрузка фона
    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile("Textures/map.png")) 
    {
        std::cerr << "ERROR: Failed to load map.png!" << std::endl;
        return 1;
    }
    sf::Sprite mapSprite(mapTexture);
    mapSprite.setScale(
        WINDOW_SIZE / static_cast<float>(mapTexture.getSize().x),
        WINDOW_SIZE / static_cast<float>(mapTexture.getSize().y)
    );

    initMap(); // Инициализация пней
    Pig pig; // Создание хряка
    Potato potato; // Создание потаты
    int score = 0;
    bool gameOver = false;

    // Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("Fonts/arial.ttf")) 
    { 
        std::cerr << "ERROR: Failed to load arial.ttf!" << std::endl;
        return 1;
    }

    // Настройка счёта
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    // Настройка окончания игры
    sf::Text endText;
    endText.setFont(font);
    endText.setCharacterSize(48);
    endText.setFillColor(sf::Color::Red);
    endText.setString("Khryak nakhryukalsya");
    endText.setPosition(150, WINDOW_SIZE / 2 - 30);

    sf::Clock clock;

    // Игровой цикл
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        if (!gameOver) 
        {
            pig.update(deltaTime); // Обновление хряка
            potato.update(deltaTime); // Обновление картохи

            // Проверка коллизии хряка и картхи
            if (std::hypot(pig.position.x - potato.position.x, 
                          pig.position.y - potato.position.y) < 1.0f) 
                          {
                score++;
                potato.respawn(); // Респаун картхи
                if (score >= 34) gameOver = true; // Условие завершения игры
            }

            scoreText.setString("Xruk: " + std::to_string(score));
        }

        window.clear();
        window.draw(mapSprite); // Фон

        // Отрисовка пней
        for (auto& hole : holes) 
        {
            sf::RectangleShape rect(sf::Vector2f(
                hole.width * CELL_SIZE,
                hole.height * CELL_SIZE
            ));
            rect.setPosition(hole.left * CELL_SIZE, hole.top * CELL_SIZE);
            rect.setFillColor(sf::Color(0, 0, 0, 0)); // Прозрачный цвет
            window.draw(rect);
        }

        pig.draw(window); // Отрисовка хряка
        potato.draw(window); // Отрисовка картхи
        window.draw(scoreText); // Отрисовка счёта

        if (gameOver) window.draw(endText); // Отрисовка сообщения о конце

        window.display();
    }

    return 0;
}