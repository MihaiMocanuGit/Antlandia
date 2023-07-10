#include "ChunkMap.h"

Chunk &ChunkMap::at(unsigned int x, unsigned int y)
{
    return m_chunkMap[y * m_size.x + x];
}

Chunk &ChunkMap::at(sf::Vector2u index)
{
    return at(index.x, index.y);
}

ChunkMap::ChunkMap(sf::Vector2u size) : m_size(size)
{
    m_initChunks();
}

void ChunkMap::m_initChunks()
{
    m_chunkMap.resize(m_size.x * m_size.y);


    for (unsigned int y = 0; y < m_size.y; ++y)
    {
        for (unsigned int x = 0; x < m_size.x; ++x)
        {
            this->at(x, y) = Chunk(x, y);

            if (m_isValidIndex(x-1, y-1))
                this->at(x, y).m_neighbours[0][0] = &this->at(x-1, y-1);
            if (m_isValidIndex(x, y-1))
                this->at(x, y).m_neighbours[0][1] = &this->at(x, y-1);
            if (m_isValidIndex(x+1, y-1))
                this->at(x, y).m_neighbours[0][2] = &this->at(x+1, y-1);

            if (m_isValidIndex(x-1, y))
                this->at(x, y).m_neighbours[1][0] = &this->at(x-1, y);
            if (m_isValidIndex(x, y))
                this->at(x, y).m_neighbours[1][1] = &this->at(x, y);
            if (m_isValidIndex(x+1, y))
                this->at(x, y).m_neighbours[1][2] = &this->at(x+1, y);

            if (m_isValidIndex(x-1, y+1))
                this->at(x, y).m_neighbours[2][0] = &this->at(x-1, y+1);
            if (m_isValidIndex(x, y+1))
                this->at(x, y).m_neighbours[2][1] = &this->at(x, y+1);
            if (m_isValidIndex(x+1, y+1))
                this->at(x, y).m_neighbours[2][2] = &this->at(x+1, y+1);
        }
    }

}

bool ChunkMap::m_isValidIndex(unsigned int x, unsigned int y) const
{
    return x >= 0 and x < m_size.x and y >= 0 and y < m_size.y;
}

ChunkMap::ChunkMap(unsigned int sizeX, unsigned int sizeY) : ChunkMap(sf::Vector2u(sizeX, sizeY))
{

}
