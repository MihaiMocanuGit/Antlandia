#include "Chunk.h"

Chunk::Chunk(sf::Vector2u index) : m_index{index}
{

}

Chunk::Chunk(unsigned int x, unsigned int y) : Chunk(sf::Vector2u(x, y))
{

}
