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

void m_drawAnts(World& world, sf::RenderWindow& window)
{
    for (size_t i = 0; i < world.ants().size(); ++i)
    {
        const Ant &ref_ant = world.ants()[i];
        float size = ref_ant.genericObject().body().getSize();
        sf::CircleShape shape(size);

        const sf::Vector3<unsigned char> &color = ref_ant.genericObject().body().getColor();
        sf::Color colorSf(color.x, color.y, color.z);
        shape.setFillColor(colorSf);

        sf::Vector2f position(ref_ant.genericObject().body().getPosition());
        shape.setPosition(position);

        window.draw(shape);
    }
}
void m_drawPheromones(World& world, sf::RenderWindow& window);
void m_drawFood(World& world, sf::RenderWindow& window);
void startGameLoop(World& world)
{

    sf::RenderWindow window(sf::VideoMode(world.size().x * Chunk::CHUNK_SIZE_X, world.size().y * Chunk::CHUNK_SIZE_Y), "Antlandia");
    window.setFramerateLimit(60);


    while (window.isOpen())
    {
        m_closeWindowIfEvent(window);
        window.clear(sf::Color::White);

        m_drawAnts(world, window);
        window.display();
    }
    window.close();
}
