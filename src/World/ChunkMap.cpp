#include "ChunkMap.h"

ChunksPaired ChunkMap::at(int x, int y)
{
    return m_primitiveMaps.at(y * m_size.x + x);
}

ChunksPaired ChunkMap::at(sf::Vector2i index)
{
    return at(index.x, index.y);
}

ChunkMap::ChunkMap(sf::Vector2u size, SpecializedVectorAllTypes &allWorldObjects) : m_size(size)
{
    m_initMaps(allWorldObjects);
}

ChunkMap::ChunkMap(sf::Vector2u size, SpecializedVectorAllTypes &&allWorldObjects) : ChunkMap(size, allWorldObjects)
{
}


ChunkMap::ChunkMap(unsigned int sizeX, unsigned int sizeY, SpecializedVectorAllTypes &allWorldObjects) : ChunkMap(sf::Vector2u(sizeX, sizeY), allWorldObjects)
{
}
ChunkMap::ChunkMap(unsigned int sizeX, unsigned int sizeY, SpecializedVectorAllTypes &&allWorldObjects) : ChunkMap(sizeX, sizeY, allWorldObjects)
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



void ChunkMap::m_initMaps(SpecializedVectorAllTypes &allWorldObjects)
{
    m_initChunks(m_primitiveMaps.antMap, allWorldObjects.ref_worldAnts);
    m_initChunks(m_primitiveMaps.pheromoneMap,  allWorldObjects.ref_worldPheromones);
    m_initChunks(m_primitiveMaps.foodMap,  allWorldObjects.ref_worldFoods);
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
