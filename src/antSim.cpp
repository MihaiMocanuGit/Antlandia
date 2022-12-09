#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <string>

#include "god.h"

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
void initAnts(God<SIZE_X, SIZE_Y> &god, const sf::Vector2u &windowSize)
{
    god.ants.createNewObjects((1 << 6) * SIZE_X * SIZE_Y);

    srand(time(0));

    for(auto & ant : god.ants.newObjects)
    {
        sf::CircleShape shape(1);
        shape.setFillColor(sf::Color::Black);
        shape.setPosition(tempTestRand(0, windowSize.x), tempTestRand(0, windowSize.y));

        sf::Vector2f velocity{0.07, 0.1};
        ant.init(shape, velocity, 100, 100, 5);
       
    }


    god.ants.insertAllNewObjectsIntoHolder();
    god.insertAntHolderIntoWorldChunks();

}

template<std::size_t SIZE_X, std::size_t SIZE_Y>
void startApp(God<SIZE_X, SIZE_Y> &god, const sf::Vector2u &windowSize, const std::string &windowTitle)
{

    initAnts(god, windowSize);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), windowTitle);
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        closeWindowIfEvent(window);

        //clear screen and fill with background color
        window.clear(sf::Color::White);


        for(unsigned int i = 0; i < god.ants.inUseObjects.size(); i++)
        {
            Ant *pCurrentAnt = &god.ants.inUseObjects[i];

            sf::Vector2f offset{tempTestRand(-0.75*1.25, 1*1.25), tempTestRand(-0.75*1.5, 1*1.5)};
            pCurrentAnt->template moveBy(god, offset);

            window.draw(pCurrentAnt->getShape());
        }
        window.display();
    }
    
    window.close();
}

int main()
{

    God<15,15> god;


    
    const sf::Vector2u windowSize = {god.NO_OF_CHUNKS_X * Chunk::CHUNK_SIZE.x, god.NO_OF_CHUNKS_Y * Chunk::CHUNK_SIZE.y};
    startApp(god, windowSize, "AntLandia :)");
    
    return 0;
}
