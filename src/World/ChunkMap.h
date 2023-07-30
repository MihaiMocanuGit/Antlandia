#pragma once
#include "Chunk.h"


struct ChunksPaired
{
    Chunk<Ant> &ref_antChunk;
    Chunk<Pheromone> &ref_pheromoneChunk;
    Chunk<Food> &ref_foodChunk;

    ChunksPaired() = delete;
    ChunksPaired(Chunk<Ant> &ref_antChunk, Chunk<Pheromone> &ref_pheromoneChunk, Chunk<Food> &ref_foodChunk);

};



struct PrimitiveChunkMaps
{

    PrimitiveChunkMap_t<Ant> antMap = {};
    PrimitiveChunkMap_t<Pheromone> pheromoneMap = {};
    PrimitiveChunkMap_t<Food> foodMap = {};

    ChunksPaired at(int index)
    {
        return ChunksPaired{antMap[index], pheromoneMap[index], foodMap[index]};
    }
};


class ChunkMap
{
private:
    PrimitiveChunkMaps m_primitiveMaps;

    sf::Vector2u m_size = {0, 0};

    [[nodiscard]] inline bool m_isValidIndex(unsigned x, unsigned y) const;

    template <class T>
    void m_initChunks(std::vector<Chunk<T>> &objectMap);
    void m_initMaps();

    int m_xyToIndex(int x, int y) const;
public:
    ChunkMap() = default;
    explicit ChunkMap(sf::Vector2u size);
    ChunkMap(unsigned sizeX, unsigned sizeY);

    ChunksPaired at(sf::Vector2i index);
    ChunksPaired at(int x, int y);
    template <class T>
    Chunk<T>& at(int x, int y, std::vector<Chunk<T>> &objectMap);
    template <class T>
    Chunk<T>& at(int x, int y, std::vector<Chunk<T>> &objectMap) const;

    PrimitiveChunkMaps &primitiveChunkMaps();
    const PrimitiveChunkMaps &primitiveChunkMaps() const;

    sf::Vector2i computeHomeChunk(const sf::Vector2f &position) const;
    [[nodiscard]] sf::Vector2u size() const;
};

template <class T>
void ChunkMap::m_initChunks(std::vector<Chunk<T>> &objectMap)
{
    objectMap.resize(m_size.x * m_size.y);


    for (unsigned int y = 0; y < m_size.y; ++y)
    {
        for (unsigned int x = 0; x < m_size.x; ++x)
        {
            this->at(x, y, objectMap) = Chunk<T>(x, y);

            if (m_isValidIndex(x-1, y-1))
                this->at(x, y, objectMap).m_neighbours[0][0] = &this->at(x-1, y-1, objectMap);
            if (m_isValidIndex(x, y-1))
                this->at(x, y, objectMap).m_neighbours[0][1] = &this->at(x, y-1, objectMap);
            if (m_isValidIndex(x+1, y-1))
                this->at(x, y, objectMap).m_neighbours[0][2] = &this->at(x+1, y-1, objectMap);

            if (m_isValidIndex(x-1, y))
                this->at(x, y, objectMap).m_neighbours[1][0] = &this->at(x-1, y, objectMap);
            if (m_isValidIndex(x, y))
                this->at(x, y, objectMap).m_neighbours[1][1] = &this->at(x, y, objectMap);
            if (m_isValidIndex(x+1, y))
                this->at(x, y, objectMap).m_neighbours[1][2] = &this->at(x+1, y, objectMap);

            if (m_isValidIndex(x-1, y+1))
                this->at(x, y, objectMap).m_neighbours[2][0] = &this->at(x-1, y+1, objectMap);
            if (m_isValidIndex(x, y+1))
                this->at(x, y, objectMap).m_neighbours[2][1] = &this->at(x, y+1, objectMap);
            if (m_isValidIndex(x+1, y+1))
                this->at(x, y, objectMap).m_neighbours[2][2] = &this->at(x+1, y+1, objectMap);
        }
    }

}

template <class T>
Chunk<T> &ChunkMap::at(int x, int y, std::vector<Chunk<T>> &objectMap) const
{
    return objectMap[m_xyToIndex(x, y)];
}

template <class T>
Chunk<T> &ChunkMap::at(int x, int y, std::vector<Chunk<T>> &objectMap)
{
    return objectMap[m_xyToIndex(x, y)];
}