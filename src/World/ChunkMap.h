#pragma once
#include "Chunk.h"


struct AllChunksTypes
{
    Chunk<Ant> &ref_antChunk;
    Chunk<Pheromone> &ref_pheromoneChunk;
    Chunk<Food> &ref_foodChunk;

    AllChunksTypes(Chunk<Ant> &ref_antChunk, Chunk<Pheromone> &ref_pheromoneChunk, Chunk<Food> &ref_foodChunk);

};

struct Maps
{
    //we will consider it to be a matrix
    std::vector<Chunk<Ant>> antMap = {};
    std::vector<Chunk<Pheromone>> pheromoneMap = {};
    std::vector<Chunk<Food>> foodMap = {};

    AllChunksTypes at(int index)
    {
        return AllChunksTypes{antMap[index], pheromoneMap[index], foodMap[index]};
    }
};


class ChunkMap
{
private:
    //we will consider it to be a matrix
    Maps m_maps;

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

    AllChunksTypes at(sf::Vector2i index);
    AllChunksTypes at(int x, int y);
    template <class T>
    Chunk<T>& at(int x, int y, std::vector<Chunk<T>> &objectMap);
    template <class T>
    Chunk<T>& at(int x, int y, std::vector<Chunk<T>> &objectMap) const;

    Maps &maps();
    const Maps &maps() const;

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
