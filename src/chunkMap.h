#ifndef CHUNK_MAP_H
#define CHUNK_MAP_H

#include <array>

#include "chunk.h"
#include "ant.h"

template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
class ChunkMap
{
private:
    //create chunk map and inits all chunks
    void m_initChunkMap()
    {
        for (unsigned int y = 0; y < map.size(); y++)
        {
            for (unsigned int x = 0; x < map[y].size(); x++)
            {
                map[y][x] = Chunk({x, y});
            }
        }
        Chunk::initAllChunks(map);
    }

public:
    std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> map;

    ChunkMap()
    {
        m_initChunkMap();
    }


    bool objectPositionFitsChunkMap(const sf::Vector2f &position)
    {

        if (position.x >= 0 and position.y >= 0)
            if (position.x <= Chunk::CHUNK_SIZE.x * MAP_SIZE_X and position.y <= Chunk::CHUNK_SIZE.y * MAP_SIZE_Y)
                return true;
            else
                return false;
        else
            return false;
    }


    sf::Vector2u identifyChunkMapIndexFromPosition(const sf::Vector2f &position)
    {
        if (objectPositionFitsChunkMap(position))
        {

            unsigned int xIndex = position.x / Chunk::CHUNK_SIZE.x;
            unsigned int yIndex = position.y / Chunk::CHUNK_SIZE.y;

            //indexes are from 0 to (MAP_SIZE_ - 1), so if an ant is right on the edge, it would be out of bonds
            //to correct this, the chunks on the last row/column are made ever so slighty bigger
            if (xIndex == MAP_SIZE_X) xIndex--;
            if (yIndex == MAP_SIZE_Y) yIndex--;

            return {xIndex, yIndex};
        } else
        {
            throw std::domain_error("object position doesn't fit into map");
        }
    }

};


#endif //CHUNK_MAP_H
