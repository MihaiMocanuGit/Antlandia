#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <string>
#include <algorithm>

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
    rWorld.antController.objectHolder.createNewObjects((1 << 0));


    srand(time(0));

    for(auto & ant : rWorld.antController.objectHolder.newObjects)
    {
        sf::CircleShape shape(1.5);
        shape.setFillColor(sf::Color::Black);

        sf::Vector2f middlePoint(SIZE_X*Chunk::CHUNK_SIZE.x/2.0,
                                 SIZE_Y*Chunk::CHUNK_SIZE.y/2.0);
        sf::Vector2f  offset(Chunk::CHUNK_SIZE.x/1.5,
                             Chunk::CHUNK_SIZE.y/1.5);
        shape.setPosition(tempTestRand(middlePoint.x - offset.x, middlePoint.x + offset.x),
                          tempTestRand(middlePoint.x - offset.x, middlePoint.x + offset.x));

        sf::Vector2f velocity{0.07, 0.1};
        ant.init(shape, velocity, 100, 100, 5);
       
    }


    rWorld.antController.objectHolder.moveAllNewObjectsIntoHolder();
    rWorld.antController.insertObjectHolderIntoWorldChunks();

}

void modifyOriginByKeyboard(sf::Vector2f &rOrigin, float maxSpeed)
{
    constexpr float STEP = 0.1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        // move up...
        rOrigin.y -= STEP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        // move down...
        rOrigin.y += STEP;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        // move left...
        rOrigin.x -= STEP;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        // move right...
        rOrigin.x += STEP;
    }

    rOrigin.x = std::clamp(rOrigin.x, -maxSpeed, maxSpeed);
    rOrigin.y = std::clamp(rOrigin.y, -maxSpeed, maxSpeed);
}

Pheromone getGenericPheromone()
{
    sf::CircleShape shape(1);
    shape.setFillColor(sf::Color::Green);
    Pheromone pheromone(shape, 2, 100, 1.25);

    return pheromone;
}
template<std::size_t SIZE_X, std::size_t SIZE_Y>
void startApp(World<SIZE_X, SIZE_Y> &rWorld, const sf::Vector2u &windowSize, const std::string &windowTitle)
{
    initAnts(rWorld, windowSize);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), windowTitle);
    window.setFramerateLimit(60);

    sf::Vector2f origin(0, 0);
    sf::Vector2f boundary(1.5, 1.5);
    /*
     * Random movement logic
     * x: _______-1.0____0.0____1.0_______
     * (user changes origin, eg (0.5,0.5)
     * x: _________-0.5____0.5____1.5_____
     */
    while (window.isOpen())
    {
        closeWindowIfEvent(window);

        //clear screen and fill with background color
        window.clear(sf::Color::White);

        std::vector<Ant> *pInUseAnts = &rWorld.antController.objectHolder.inUseObjects;
        modifyOriginByKeyboard(origin, 1);
        for(auto & ant : *pInUseAnts)
        {
            sf::Vector2f offset{tempTestRand(origin.x - boundary.x, origin.x + boundary.x),
                                tempTestRand(origin.y - boundary.y, origin.y + boundary.y)};
            ant.template moveBy(rWorld, offset);

            sf::CircleShape shape(1);
            shape.setFillColor(sf::Color::Green);
            Pheromone pheromone(shape, 2, 100, 1.25);

            ant.template dischargePheromone(rWorld, pheromone);

            window.draw(ant.getShape());
        }

        std::vector<Pheromone> *pInUsePheromons = &rWorld.pheromoneController.objectHolder.inUseObjects;
        for(auto & pheromone : *pInUsePheromons)
        {
            window.draw(pheromone.getShape());
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
