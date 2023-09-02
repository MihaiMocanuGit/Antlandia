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
    assert(not isPositionOutsideBounds(position));

    sf::Vector2i chunkIndex(position.x/Chunk<void>::CHUNK_SIZE_X, position.y/Chunk<void>::CHUNK_SIZE_Y);
    return chunkIndex;
}



void ChunkMap::m_initMaps(SpecializedVectorAllTypes &allWorldObjects)
{
    m_initChunks(m_primitiveMaps.antMap, allWorldObjects.r_worldAnts);
    m_initChunks(m_primitiveMaps.pheromoneMap,  allWorldObjects.r_worldPheromones);
    m_initChunks(m_primitiveMaps.foodMap,  allWorldObjects.r_worldFood);
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

bool ChunkMap::spotsAreInSameChunk(const sf::Vector2f &position1, const sf::Vector2f &position2) const
{
    return computeChunkIndex(position1) == computeChunkIndex(position2);
}

bool ChunkMap::isPositionOutsideBounds(const sf::Vector2f &position) const
{
    return position.x < 0 or position.x >= (float)(m_size.x * Chunk<void>::CHUNK_SIZE_X)
            or position.y < 0 or position.y >= (float)(m_size.y * Chunk<void>::CHUNK_SIZE_Y);
}

CornerBounds ChunkMap::computeBoundarySubRegion(const sf::Vector2f origin, const float radiusSubRegion) const
{
    assert(not r_world.map().isPositionOutsideBounds(r_ant.body().getPosition()));

    //we need to check the chunks that intersect with the ant's interact radius,
    //so we compute the bounds of the zone of interaction
    const sf::Vector2f center = origin;
    const float MAX_VALUE_X = (float)size().x * Chunk<int>::CHUNK_SIZE_X;
    const float MAX_VALUE_Y = (float)size().y * Chunk<int>::CHUNK_SIZE_Y;

    //we clamp the bounds inside the world bound
    float left = std::clamp(center.x - radiusSubRegion, 0.0f, MAX_VALUE_X - 0.001f);
    float right = std::clamp(center.x + radiusSubRegion, 0.0f, MAX_VALUE_X - 0.001f);

    float up = std::clamp(center.y - radiusSubRegion, 0.0f, MAX_VALUE_Y - 0.001f);
    float down = std::clamp(center.y + radiusSubRegion, 0.0f, MAX_VALUE_Y - 0.001f);

    const sf::Vector2i upperLeft = computeChunkIndex({left, up});
    const sf::Vector2i lowerRight = computeChunkIndex({right, down});

    return {upperLeft, lowerRight};
}
ChunksPaired::ChunksPaired(Chunk<Ant> &ref_antChunk, Chunk<Pheromone> &ref_pheromoneChunk,
                           Chunk<Food> &ref_foodChunk)
        : ref_antChunk{ref_antChunk}, ref_pheromoneChunk{ref_pheromoneChunk}, ref_foodChunk{ref_foodChunk}
{}
