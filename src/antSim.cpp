#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "objectOrganizer.h"


/*
template<std::size_t SIZE_X, std::size_t SIZE_Y>
void initEmptyChunks(std::array<std::array<Chunk, SIZE_X>, SIZE_Y> &chunks) 
{
    for(unsigned int y = 0; y < chunks.size(); y++)
    {
        for(unsigned int x = 0; x < chunks[y].size(); x++)
        {
            chunks[y][x] = Chunk({x,y});
        }
    }
    
    Chunk::initAllChunks(chunks);    
}
*/

void closeWindowIfEvent(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

template<std::size_t SIZE_X, std::size_t SIZE_Y>
void startApp(ObjectOrganizer<SIZE_X, SIZE_Y> &objectOrganizer, const sf::Vector2u &windowSize, const std::string &windowTitle)
{

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), windowTitle);
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        closeWindowIfEvent(window);

        //clear screen and fill with background color
        window.clear(sf::Color::White);

        window.display();
    }

    window.close();
}


int main()
{
    /*
    constexpr int CHUNK_MAP_SIZE_X = 5;
    constexpr int CHUNK_MAP_SIZE_Y = 10;
    std::array<std::array<Chunk, CHUNK_MAP_SIZE_X>, CHUNK_MAP_SIZE_Y> chunkMap; 
    */

    ObjectOrganizer<5,10> objectOrganizer;

    const sf::Vector2u windowSize = {objectOrganizer.noOfChunksX * Chunk::CHUNK_SIZE.x, objectOrganizer.noOfChunksY * Chunk::CHUNK_SIZE.y};
    startApp(objectOrganizer, windowSize, "AntLandia :)");   

    return 0;
}
