#include <iostream>
#include <SFML/Graphics.hpp>

#include "ant.h"
#include "chunk.h"

void initChunks(std::array<std::array<Chunk, 8>, 8> &chunks) 
{
    for(int y = 0; y < chunks.size(); y++)
    {
        for(int x = 0; x < chunks[y].size(); x++)
        {
            chunks[y][x] = Chunk(x,y);
        }
    }
    
    Chunk::chunksInit(chunks);    
}

void initSFML(std::array<std::array<Chunk, 8>, 8> &chunks)
{

    sf::RenderWindow window(sf::VideoMode(8 * Chunk::chunkSizeX, 8 * Chunk::chunkSizeY), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        int colorCount = 0;
        for (int y = 0; y < 8; y++)
        {
                for(int x = 0; x < 8; x++)
                {
                    sf::RectangleShape rectangle(sf::Vector2f(Chunk::chunkSizeX, Chunk::chunkSizeY));
                    
                    rectangle.setPosition(x * Chunk::chunkSizeX, y * Chunk::chunkSizeY);                    
                    
                    sf::Color colors[6] = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan};
                    
                    rectangle.setFillColor(colors[colorCount++]);
                    
                    if(colorCount == 6) colorCount = 0;

                    window.draw(rectangle);
                }
        }

        window.display();
    }
}

int main()
{
	std::cout << "It works!\n";
	


	Ant ant(2, 3, NULL);
	ant.initAnt(99.9f, 69, 2, 0);
	ant.initGenericObject(1, 0.5, 3);

	std::cout << ant.size << '\n';
    
    std::array<std::array<Chunk, 8>, 8> chunks;
    initChunks(chunks);  

    initSFML(chunks);   

    return 0;
}
