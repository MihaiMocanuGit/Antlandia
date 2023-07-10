#include "Chunk.h"
const sf::Vector2u Chunk::CHUNK_SIZE = {32, 32};

Chunk::Chunk(sf::Vector2u index) : m_index{index}
{

}

Chunk::Chunk(unsigned int x, unsigned int y) : Chunk(sf::Vector2u(x, y))
{

}
