#include "Antlandia.h"

void m_addObjects(World &world)
{
    world.prepareAnt(sf::Vector2f(300.0f, 300.0f), 10.0f);
    world.ants().finishChanges();

    for (unsigned y = 0; y < world.size().y; ++y)
    {
        for (unsigned x = 0; x < world.size().x; ++x)
        {
            world.map().at(x, y).ref_antChunk.objects.finishChanges();
            world.map().at(x, y).ref_pheromoneChunk.objects.finishChanges();
            world.map().at(x, y).ref_foodChunk.objects.finishChanges();
        }
    }

    /*
    for (int i = 0; i < 125; ++i)
    {
        world.prepareAnt(sf::Vector2f(i * 5.0f, i * 5.0f));
        world.prepareFood(sf::Vector2f(world.size().x * Chunk<void>::CHUNK_SIZE_X - i * 5.0f, i * 5.0f));

        if (i % 2 == 0)
            world.preparePheromone(sf::Vector2f((float) world.size().x * Chunk<void>::CHUNK_SIZE_X / 2, i * 5.0f));
        else
            world.preparePheromone(sf::Vector2f(i * 5.0f, (float) world.size().y * Chunk<void>::CHUNK_SIZE_Y / 2));
    }

    world.ants().finishChanges();
    world.food().finishChanges();
    world.pheromones().finishChanges();

    for (unsigned y = 0; y < world.size().y; ++y)
    {
        for (unsigned x = 0; x < world.size().x; ++x)
        {
            world.map().at(x, y).ref_antChunk.objects.finishChanges();
            world.map().at(x, y).ref_pheromoneChunk.objects.finishChanges();
            world.map().at(x, y).ref_foodChunk.objects.finishChanges();
        }
    }
    */
}

void startApp()
{
    World world(10, 10);
    m_addObjects(world);

    startGameLoop(world);
}