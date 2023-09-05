#include <thread>

#include "AppLogic.h"
#include "../AntActions/AntActions.h"
#include "../Utils/Utils.h"


static unsigned frameCount = 0;
void m_closeWindowIfEvent(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void m_drawAnts(const World &world, sf::RenderWindow &window)
{
    for (size_t i = 0; i < world.ants().size(); ++i)
        window.draw(getShape(world.ants()[i].body()));
}

void m_drawPheromones(const World &world, sf::RenderWindow &window)
{
    for (size_t i = 0; i < world.pheromones().size(); ++i)
        window.draw(getShape(world.pheromones()[i].body()));
}

void m_drawFood(const World &world, sf::RenderWindow &window)
{
    for (size_t i = 0; i < world.food().size(); ++i)
        window.draw(getShape(world.food()[i].body()));
}
//TODO: Delete after debug
sf::Vector2f direction = {0, 0};
void m_getInput(World &world, sf::RenderWindow &window)
{
    const sf::Vector2f UPWARDS = {0, -1};
    const sf::Vector2f DOWNWARDS = -UPWARDS;
    const sf::Vector2f RIGHT = {1, 0};
    const sf::Vector2f LEFT = -RIGHT;

    sf::Vector2f result = {0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        result += UPWARDS;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        result += DOWNWARDS;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        result += LEFT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        result += RIGHT;

    direction = result;
}

void m_prepareNextAntState(World &world, const sf::Vector2i &chunkIndex, std::vector<sf::CircleShape> &r_renderBuffer)
{
    Chunk<Ant> &r_chunkAnt = world.map().at(chunkIndex).r_antChunk;
    size_t size = r_chunkAnt.objects.size();
    for (size_t i = 0; i < size ; ++i)
    {
        Ant &r_ant = world.ants()[r_chunkAnt.objects[size - 1 - i].index];
        //world.moveBy(r_ant.genericObject(), direction);
        switch (r_ant.action())
        {
            case Ant::Action_e::SearchingFood:
                AntActions::searchFood(r_ant, world, frameCount);
                break;
            case Ant::Action_e::GrabbingFood:
                AntActions::grabFood(r_ant, world, frameCount);
                break;
            case Ant::Action_e::BringingFood:
                AntActions::bringFood(r_ant, world, frameCount);
                break;
            default:
                break;
        }

        assert((r_ant.knowledge().homeChunkIndexes() != sf::Vector2i{-1, -1}));
        r_renderBuffer.push_back(getShape(r_ant.body()));
    }
}
void m_prepareNextPheromoneState(World &world, const sf::Vector2i &chunkIndex, std::vector<sf::CircleShape> &r_renderBuffer)
{
    Chunk<Pheromone> &r_chunkPhero = world.map().at(chunkIndex).r_pheromoneChunk;
    size_t size = r_chunkPhero.objects.size();
    for (size_t i = 0; i < size; ++i)
    {
        Pheromone &r_phero = world.pheromones()[r_chunkPhero.objects[size - 1 - i].index];
        if (not r_phero.decreasePotency())
        {
            r_chunkPhero.objects.toBeRemoved(r_phero.knowledge().indexInHomeChunk());
            world.pheromones().toBeRemoved(r_phero.knowledge().indexInWorld());
        }
        r_renderBuffer.push_back(getShape(r_phero.body()));
    }
}
void m_prepareNextFoodState(World &world, const sf::Vector2i &chunkIndex, std::vector<sf::CircleShape> &r_renderBuffer)
{
    Chunk<Food> &r_chunkFood = world.map().at(chunkIndex).r_foodChunk;
    size_t size = r_chunkFood.objects.size();
    for (size_t i = 0; i < size; ++i)
    {
        Food &r_food = world.food()[r_chunkFood.objects[size - 1 - i].index];
        r_renderBuffer.push_back(getShape(r_food.body()));
    }
}
void m_prepareNextState(World &world, const sf::Vector2i &chunkIndex, std::vector<sf::CircleShape> &r_renderBuffer)
{
    m_prepareNextAntState(world, chunkIndex, r_renderBuffer);
    m_prepareNextFoodState(world, chunkIndex, r_renderBuffer);
    m_prepareNextPheromoneState(world, chunkIndex, r_renderBuffer);

}
void m_updateState(World &world)
{
    world.ants().finishChanges();
    world.pheromones().finishChanges();
    world.food().finishChanges();

    for (unsigned y = 0;  y < world.size().y ; y++)
    {
        for (unsigned x = 0;  x < world.size().x ; x++)
        {
            world.map().at(x, y).r_antChunk.objects.finishChanges();
            world.map().at(x, y).r_pheromoneChunk.objects.finishChanges();
            world.map().at(x, y).r_foodChunk.objects.finishChanges();
        }
    }
}

void m_drawScreen(sf::RenderWindow &window, std::vector<sf::CircleShape> &r_renderBuffer)
{
    window.clear(sf::Color::White);

    while(not r_renderBuffer.empty())
    {
        window.draw(r_renderBuffer.back());
        r_renderBuffer.pop_back();
    }

    window.display();
}



void startGameLoop(World& world)
{

    const sf::Vector2u windowSize = {world.size().x * Chunk<void>::CHUNK_SIZE_X + 1,
                                     world.size().y * Chunk<void>::CHUNK_SIZE_Y + 1};
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Antlandia");
    window.setFramerateLimit(30);

    std::vector<sf::CircleShape> prevRenderBuffer;
    window.setActive(false);
    while (window.isOpen())
    {
        m_closeWindowIfEvent(window);
        //m_getInput(world, window);

        std::thread drawThread(m_drawScreen, std::ref(window), std::ref(prevRenderBuffer));

        std::vector<sf::CircleShape> nextRenderBuffer;
        nextRenderBuffer.reserve(world.pheromones().size() + world.ants().size() + world.food().size());
        for (unsigned y = 0; y < world.size().y; ++y)
        {
            for (unsigned  x = 0; x < world.size().x; ++x)
            {
                m_prepareNextState(world, sf::Vector2i{ (int)x, (int)y }, nextRenderBuffer);
            }
        }

        m_updateState(world);

        drawThread.join();
        assert(prevRenderBuffer.empty());
        prevRenderBuffer = std::move(nextRenderBuffer);

        frameCount++;
    }
    window.close();
}

