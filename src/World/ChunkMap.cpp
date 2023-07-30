#include "ChunkMap.h"

ChunksPaired ChunkMap::at(int x, int y)
{
    return m_primitiveMaps.at(y * m_size.x + x);
}

ChunksPaired ChunkMap::at(sf::Vector2i index)
{
    return at(index.x, index.y);
}

ChunkMap::ChunkMap(sf::Vector2u size) : m_size(size)
{
    m_initMaps();
}




ChunkMap::ChunkMap(unsigned int sizeX, unsigned int sizeY) : ChunkMap(sf::Vector2u(sizeX, sizeY))
{

}

sf::Vector2u ChunkMap::size() const
{
    return m_size;
}

sf::Vector2i ChunkMap::computeChunkIndex(const sf::Vector2f &position) const
{
    sf::Vector2i chunkIndex(position.x/Chunk<void>::CHUNK_SIZE_X, position.y/Chunk<void>::CHUNK_SIZE_Y);
    return chunkIndex;
}



void ChunkMap::m_initMaps()
{
    m_initChunks(m_primitiveMaps.antMap);
    m_initChunks(m_primitiveMaps.pheromoneMap);
    m_initChunks(m_primitiveMaps.foodMap);
}

PrimitiveChunkMaps &ChunkMap::primitiveChunkMaps()
{
    return m_primitiveMaps;
}

const PrimitiveChunkMaps &ChunkMap::primitiveChunkMaps() const
{
    return m_primitiveMaps;
}

int ChunkMap::m_xyToIndex(int x, int y) const
{
    return y * m_size.x + x;
}

ChunksPaired::ChunksPaired(Chunk<Ant> &ref_antChunk, Chunk<Pheromone> &ref_pheromoneChunk,
                           Chunk<Food> &ref_foodChunk)
        : ref_antChunk{ref_antChunk}, ref_pheromoneChunk{ref_pheromoneChunk}, ref_foodChunk{ref_foodChunk}
{}
