#include "AppLogic.h"

#include "../Utils/Utils.h"

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

void m_getInput(World &world, sf::RenderWindow &window)
{

}

void m_prepareNextState(World &world, const sf::Vector2i &chunkIndex, sf::RenderWindow &window)
{
    Chunk<Ant> &r_chunkAnt = world.map().at(chunkIndex).ref_antChunk;
    for (int i = 0; i < r_chunkAnt.objects.size(); ++i)
    {
        Ant &r_ant = r_chunkAnt.objects.at(i).ptrWorldObjects->at(r_chunkAnt.objects.at(i).index);
        world.moveTo(r_ant.genericObject(), r_ant.body().getPosition() / 1.5f);
    }
}
void m_updateState(World &world, sf::RenderWindow &window)
{
    world.ants().addAll();
    world.pheromones().addAll();
    world.food().addAll();

    for (int y = 0;  y < world.size().y ; y++)
    {
        for (int x = 0;  x < world.size().x ; x++)
        {
            world.map().at(x, y).ref_antChunk.objects.addAll();
            world.map().at(x, y).ref_pheromoneChunk.objects.addAll();
            world.map().at(x, y).ref_foodChunk.objects.addAll();
        }
    }
}

void m_refreshScreen(const World &world, sf::RenderWindow &window)
{
    window.clear(sf::Color::White);

    m_drawPheromones(world, window);
    m_drawFood(world, window);
    m_drawAnts(world, window);

    window.display();
}



void startGameLoop(World& world)
{

    sf::RenderWindow window(sf::VideoMode(world.size().x * Chunk<void>::CHUNK_SIZE_X, world.size().y * Chunk<void>::CHUNK_SIZE_Y), "Antlandia");
    window.setFramerateLimit(60);


    while (window.isOpen())
    {
        m_closeWindowIfEvent(window);
        m_getInput(world, window);

        for (int y = 0;  y < world.size().y ; y++)
        {
            for (int x = 0;  x < world.size().x ; x++)
            {
                m_prepareNextState(world, sf::Vector2i{x, y}, window);
            }
        }

        
        m_updateState(world, window);
        m_refreshScreen(world, window);


    }
    window.close();
}

