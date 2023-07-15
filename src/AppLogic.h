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




sf::CircleShape getShape(const Body &body)
{
    float size = body.getSize();
    sf::CircleShape shape(size);

    const sf::Vector3<unsigned char> &color = body.getColor();
    sf::Color colorSf(color.x, color.y, color.z);
    shape.setFillColor(colorSf);

    sf::Vector2f position(body.getPosition());
    shape.setPosition(position);

    return shape;
}
void m_drawAnts(World& world, sf::RenderWindow& window)
{
    for (size_t i = 0; i < world.ants().size(); ++i)
        window.draw(getShape(world.ants()[i].body()));
}
void m_drawPheromones(World& world, sf::RenderWindow& window)
{
    for (size_t i = 0; i < world.ants().size(); ++i)
        window.draw(getShape(world.pheromones()[i].body()));
}
void m_drawFood(World& world, sf::RenderWindow& window)
{
    for (size_t i = 0; i < world.ants().size(); ++i)
        window.draw(getShape(world.food()[i].body()));
}

void startGameLoop(World& world)
{

    sf::RenderWindow window(sf::VideoMode(world.size().x * Chunk<void>::CHUNK_SIZE_X, world.size().y * Chunk<void>::CHUNK_SIZE_Y), "Antlandia");
    window.setFramerateLimit(60);


    while (window.isOpen())
    {
        m_closeWindowIfEvent(window);
        window.clear(sf::Color::White);

        m_drawPheromones(world, window);
        m_drawFood(world, window);
        m_drawAnts(world, window);

        window.display();
    }
    window.close();
}
