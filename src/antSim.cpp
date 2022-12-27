#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <string>

#include "world.h"


void closeWindowIfEvent(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

float tempTestRand(float LO, float HI)
{
    return LO + static_cast <float> (std::rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
}

template<std::size_t SIZE_X, std::size_t SIZE_Y>
void initAnts(World<SIZE_X, SIZE_Y> &rWorld, const sf::Vector2u &windowSize)
{
    //rWorld.ants.createNewObjects((1 << 6) * SIZE_X * SIZE_Y);
    rWorld.antController.objectHolder.createNewObjects((1 << 6) * SIZE_X * SIZE_Y);


    srand(time(0));

    for(auto & ant : rWorld.antController.objectHolder.newObjects)
    {
        sf::CircleShape shape(1);
        shape.setFillColor(sf::Color::Black);
        shape.setPosition(tempTestRand(0, windowSize.x), tempTestRand(0, windowSize.y));

        sf::Vector2f velocity{0.07, 0.1};
        ant.init(shape, velocity, 100, 100, 5);
       
    }


    rWorld.antController.objectHolder.insertAllNewObjectsIntoHolder();
    rWorld.insertAntHolderIntoWorldChunks();

}

template<std::size_t SIZE_X, std::size_t SIZE_Y>
void startApp(World<SIZE_X, SIZE_Y> &rWorld, const sf::Vector2u &windowSize, const std::string &windowTitle)
{
    initAnts(rWorld, windowSize);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), windowTitle);
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        closeWindowIfEvent(window);

        //clear screen and fill with background color
        window.clear(sf::Color::White);

        std::vector<Ant> *pInUseAnts = &rWorld.antController.objectHolder.inUseObjects;
        for(auto & ant : *pInUseAnts)
        {
            sf::Vector2f offset{tempTestRand(-0.75*1.25, 1*1.25), tempTestRand(-0.75*1.5, 1*1.5)};
            ant.template moveBy(rWorld, offset);

            window.draw(ant.getShape());
        }
        window.display();

    }
    
    window.close();
}


int main()
{

    World<15,15> world;

    
    const sf::Vector2u windowSize = {world.NO_OF_CHUNKS_X * Chunk::CHUNK_SIZE.x, world.NO_OF_CHUNKS_Y * Chunk::CHUNK_SIZE.y};
    startApp(world, windowSize, "AntLandia :)");
    
    return 0;
}
