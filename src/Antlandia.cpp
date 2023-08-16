#include <random>
#include "Antlandia.h"

void m_addObjects(World &world)
{
    const sf::Vector2f middle = {(float)world.size().x * Chunk<int>::CHUNK_SIZE_X / 2,
                                 (float)world.size().y * Chunk<int>::CHUNK_SIZE_Y / 2};

    const sf::Vector2f homeSpot = {( 2.0f * 0.0f + middle.x) / 3,
                                   ( 2.0f * 0.0f + middle.y) / 3};

    std::random_device rd;
    std::mt19937 gen(rd());
    constexpr float radius = 50;
    std::uniform_real_distribution<float> dist(-radius, radius);

    // add ants in the home spot
    for (int i = 0; i < 10; ++i)
    {
        const sf::Vector2f position = {homeSpot.x + dist(gen), homeSpot.y + dist(gen)};
        world.prepareAnt(position);
    }

    //mark the home spot with home pheromones
    for (int i = 0; i < 400; ++i)
    {
        const sf::Vector2f position = {homeSpot.x + dist(gen), homeSpot.y + dist(gen)};
        Body pheromoneBody = world.pheromoneTypes.HOME_PHEROMONE_BODY;
        pheromoneBody.setPosition(position);
        world.preparePheromone(pheromoneBody);
    }

    const sf::Vector2f foodSpot = {( 2.0f * (float)world.size().x * Chunk<int>::CHUNK_SIZE_X + middle.x) / 3,
                                   ( 2.0f * (float)world.size().y * Chunk<int>::CHUNK_SIZE_Y + middle.y) / 3};
    //fill the food spot with food
    for (int i = 0; i < 400; ++i)
    {
        const sf::Vector2f position = {foodSpot.x + dist(gen), foodSpot.y + dist(gen)};
        world.prepareFood(position);
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
}

void startApp()
{
    World world(12, 12);
    m_addObjects(world);

    startGameLoop(world);
}