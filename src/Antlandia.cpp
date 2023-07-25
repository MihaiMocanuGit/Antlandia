#include "Antlandia.h"

void m_addObjects(World &world)
{
    for (int i = 0; i < 125; ++i)
    {
        world.addAnt(sf::Vector2f(i * 5.0f, i * 5.0f));
        world.addFood(sf::Vector2f(world.size().x * Chunk<void>::CHUNK_SIZE_X - i * 5.0f, i * 5.0f));

        if (i % 2 == 0)
            world.addPheromone(sf::Vector2f((float) world.size().x * Chunk<void>::CHUNK_SIZE_X / 2, i * 5.0f));
        else
            world.addPheromone(sf::Vector2f(i * 5.0f, (float) world.size().y * Chunk<void>::CHUNK_SIZE_Y / 2));
    }


    world.ants().addAll();
    world.food().addAll();
    world.pheromones().addAll();
}

void startApp()
{
World world(10, 10);
m_addObjects(world);

startGameLoop(world);
}