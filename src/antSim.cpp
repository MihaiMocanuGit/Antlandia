#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "ant.h"
#include "chunk.h"



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

void closeWindowOnEvent(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

template<std::size_t SIZE_X, std::size_t SIZE_Y>
void startApp(std::array<std::array<Chunk, SIZE_X>, SIZE_Y> &chunks, const sf::Vector2u &windowSize, const std::string &windowTitle)
{

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), windowTitle);

    while (window.isOpen())
    {
        closeWindowOnEvent(window);

        window.display();
    }
}

/*
template<std::size_t SIZE_X, std::size_t SIZE_Y>
void createSomeAnts(std::array<std::array<Chunk, SIZE_X>, SIZE_Y> &chunks)
{
    constexpr int NO_ANTS = 64;
    std::array<Ant, NO_ANTS> ants;

    int colorCode = 5;
    for( auto & ant : ants)
    {   
        sf::Color colors[6] = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan};
        if(colorCode == -1) colorCode = 0;
    }
}
*/

int main()
{

	
    constexpr int CHUNK_MAP_SIZE_X = 8;
    constexpr int CHUNK_MAP_SIZE_Y = 8;
    std::array<std::array<Chunk, CHUNK_MAP_SIZE_X>, CHUNK_MAP_SIZE_Y> chunkMap;
    
    initEmptyChunks(chunkMap);  

    const sf::Vector2u windowSize = {CHUNK_MAP_SIZE_X * Chunk::CHUNK_SIZE.x, CHUNK_MAP_SIZE_Y * Chunk::CHUNK_SIZE.y};
    startApp(chunkMap, windowSize, "AntLandia :)");   

    return 0;
}
