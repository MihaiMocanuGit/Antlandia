#include <random>
#include "Antlandia.h"

void m_addObjects(World &world)
{
    const sf::Vector2f worldSize = {(float)world.size().x * Chunk<int>::CHUNK_SIZE_X,
                                    (float)world.size().y * Chunk<int>::CHUNK_SIZE_Y};
    const sf::Vector2f middle = worldSize / 2.0f;

    const sf::Vector2f homeSpot = {(0.0f + middle.x) / 2,
                                   (0.0f + middle.y) / 2};

    std::random_device rd;
    std::mt19937 gen(rd());
    constexpr float radius = 25;
    std::uniform_real_distribution<float> dist(-radius, radius);


    //add a queen in the home spot
    Ant queen = world.antTypes.QUEEN_ANT;
    queen.body().setPosition(homeSpot);
    world.prepareAnt(queen);


    // add worker ants in the home spot
    for (int i = 0; i < 32; ++i)
    {
        const float x = std::clamp(homeSpot.x + dist(gen), 0.0f, worldSize.x - 0.01f);
        const float y =  std::clamp(homeSpot.y + dist(gen), 0.0f, worldSize.y - 0.01f);;

        const sf::Vector2f position = {x, y};
        Ant ant = world.antTypes.WORKER_ANT;
        ant.body().setPosition(position);
        ant.home() = homeSpot;
        world.prepareAnt(ant);
    }

    //mark the home spot with home pheromones
    for (int i = 0; i < 400; ++i)
    {
        const float x = std::clamp(homeSpot.x + dist(gen), 0.0f, worldSize.x - 0.01f);
        const float y =  std::clamp(homeSpot.y + dist(gen), 0.0f, worldSize.y - 0.01f);;

        const sf::Vector2f position = {x, y};
        Pheromone pheromone = world.pheromoneTypes.HOME_PHEROMONE;
        pheromone.body().setPosition(position);
        world.preparePheromone(pheromone);
    }

    //const sf::Vector2f foodSpot = {( 2.0f * worldSize.x + middle.x) / 3.0f,
    //                               ( 2.0f * worldSize.y + middle.y) / 3.0f};
    const sf::Vector2f foodSpot = {(middle.x + worldSize.x) / 2.0f, (middle.y + worldSize.y) / 2.0f};
    //fill the food spot with food
    for (int i = 0; i < 400; ++i)
    {
        const float x = std::clamp(foodSpot.x + dist(gen), 0.0f, worldSize.x - 0.01f);
        const float y =  std::clamp(foodSpot.y + dist(gen), 0.0f, worldSize.y - 0.01f);

        const sf::Vector2f position = {x, y};
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
    World world(60, 60);
    m_addObjects(world);

    startGameLoop(world);
}