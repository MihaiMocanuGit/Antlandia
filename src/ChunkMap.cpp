#include "ChunkMap.h"

OverlapedChunks ChunkMap::at(int x, int y)
{
    return m_maps.at(y * m_size.x + x);
}

OverlapedChunks ChunkMap::at(sf::Vector2i index)
{
    return at(index.x, index.y);
}

ChunkMap::ChunkMap(sf::Vector2u size) : m_size(size)
{
    m_initMaps();
}


bool ChunkMap::m_isValidIndex(unsigned int x, unsigned int y) const
{
    return x >= 0 and x < m_size.x and y >= 0 and y < m_size.y;
}

ChunkMap::ChunkMap(unsigned int sizeX, unsigned int sizeY) : ChunkMap(sf::Vector2u(sizeX, sizeY))
{

}

sf::Vector2u ChunkMap::size() const
{
    return m_size;
}

sf::Vector2i ChunkMap::computeHomeChunk(const sf::Vector2f &position) const
{
    sf::Vector2i chunkIndex(position.x/Chunk<void>::CHUNK_SIZE_X, position.y/Chunk<void>::CHUNK_SIZE_Y);
    return chunkIndex;
}

void ChunkMap::m_initMaps()
{
    m_initChunks(m_maps.antMap);
    m_initChunks(m_maps.pheromoneMap);
    m_initChunks(m_maps.foodMap);
}

Maps &ChunkMap::maps()
{
    return m_maps;
}

const Maps &ChunkMap::maps() const
{
    return m_maps;
}

int ChunkMap::m_xyToIndex(int x, int y) const
{
    return y * m_size.x + x;
}

