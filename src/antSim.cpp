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
void startApp(ObjectOrganizer<SIZE_X, SIZE_Y> &objectOrganizer, const sf::Vector2u &windowSize, const std::string &windowTitle)
{
    /*
    objectOrganizer.ants.createNewObjects(256 * 2 * 100);
    srand(time(0));
    
    for(auto & ant : objectOrganizer.ants.newObjects)
    {
        ant.shape.setRadius(1);
        ant.shape.setFillColor(sf::Color::Black);
        ant.shape.setPosition(tempTestRand(0, windowSize.x), tempTestRand(0, windowSize.y));
    }
     
    objectOrganizer.ants.insertAllNewObjectsIntoHolder();
   
  
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), windowTitle);
    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        closeWindowIfEvent(window);

        //clear screen and fill with background color
        window.clear(sf::Color::White);
        
        for(auto & ant : objectOrganizer.ants.inUseObjects)
        {
            window.draw(ant.shape);

            float x = tempTestRand(0, windowSize.x);
            float y = tempTestRand(0, windowSize.y);
            ant.shape.setPosition(x, y);

            if(ant.shape.getRadius() != 1) std::cout << ant.size << ' ';
        }
        
        window.display();
    }
    
    window.close();
    */
}

int main()
{
    ObjectOrganizer<2,2> objectOrganizer;


    /*
    const sf::Vector2u windowSize = {objectOrganizer.noOfChunksX * Chunk::CHUNK_SIZE.x, objectOrganizer.noOfChunksY * Chunk::CHUNK_SIZE.y};
    startApp(objectOrganizer, windowSize, "AntLandia :)");   
    */
    return 0;
}
