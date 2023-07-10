#pragma once
#include <SFML/Graphics.hpp>

void m_closeWindowIfEvent(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void startWorld(unsigned numberOfAnts, const sf::Vector2u &noChunks)
{

    sf::RenderWindow window(sf::VideoMode(noChunks.x * Chunk::CHUNK_SIZE.x, noChunks.y * Chunk::CHUNK_SIZE.y), "Antlandia");
    window.setFramerateLimit(60);


    while (window.isOpen())
    {
        m_closeWindowIfEvent(window);


        window.clear(sf::Color::White);

        window.display();
    }
    window.close();
}
