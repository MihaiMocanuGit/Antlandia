#pragma once
#include <SFML/Graphics.hpp>

#include "World.h"

void m_closeWindowIfEvent(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void startGameLoop(World& world)
{

    sf::RenderWindow window(sf::VideoMode(world.size().x * Chunk::CHUNK_SIZE_X, world.size().y * Chunk::CHUNK_SIZE_Y), "Antlandia");
    window.setFramerateLimit(60);


    while (window.isOpen())
    {
        m_closeWindowIfEvent(window);


        window.clear(sf::Color::White);

        window.display();
    }
    window.close();
}
