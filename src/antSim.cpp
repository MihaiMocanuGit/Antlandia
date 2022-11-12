#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <string>

#include "objectOrganizer.h"

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
void initAnts(ObjectOrganizer<SIZE_X, SIZE_Y> &objectOrganizer, const sf::Vector2u &windowSize)
{
    objectOrganizer.ants.createNewObjects((1<<7) * SIZE_X * SIZE_Y);
    srand(time(0));

    for(auto & ant : objectOrganizer.ants.newObjects)
    {
        sf::CircleShape shape(1);
        shape.setFillColor(sf::Color::Black);
        shape.setPosition(tempTestRand(0, windowSize.x), tempTestRand(0, windowSize.y));

        sf::Vector2f velocity{0.07, 0.1};
        ant.init(shape, velocity, 100, 100, 5);
       
    }
     
    objectOrganizer.ants.insertAllNewObjectsIntoHolder();
    objectOrganizer.insertAntHolderIntoWorldChunks();
}

template<std::size_t SIZE_X, std::size_t SIZE_Y>
void startApp(ObjectOrganizer<SIZE_X, SIZE_Y> &objectOrganizer, const sf::Vector2u &windowSize, const std::string &windowTitle)
{
    
    
    initAnts(objectOrganizer, windowSize);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), windowTitle);
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        closeWindowIfEvent(window);

        //clear screen and fill with background color
        window.clear(sf::Color::White);

        /*
        for(auto & ant : objectOrganizer.ants.inUseObjects)
        {

            window.draw(ant.getShape());

            sf::Vector2f offset{tempTestRand(-2, 2), tempTestRand(-1.8, 2)};
            //objectOrganizer.moveAntBy(ant, offset);
        }
        */

        for(unsigned int i = 0; i < objectOrganizer.ants.inUseObjects.size(); i++)
        {
            Ant *pCurrentAnt = &objectOrganizer.ants.inUseObjects[i];

            window.draw(pCurrentAnt->getShape());

            sf::Vector2f offset{tempTestRand(-2, 2), tempTestRand(-1.8, 2)};
            objectOrganizer.moveAntAtIndexBy(i, offset);
        }
        window.display();
    }
    
    window.close();
}

int main()
{
    ObjectOrganizer<20,20> objectOrganizer;


    
    const sf::Vector2u windowSize = {objectOrganizer.noOfChunksX * Chunk::CHUNK_SIZE.x, objectOrganizer.noOfChunksY * Chunk::CHUNK_SIZE.y};
    startApp(objectOrganizer, windowSize, "AntLandia :)");
    
    return 0;
}
