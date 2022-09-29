#include "objectOrganizer.h"


template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
void ObjectOrganizer<MAP_SIZE_X, MAP_SIZE_Y>::m_initChunkMap()
{
    for(unsigned int y = 0; y < chunkMap.size(); y++)
    {
        for(unsigned int x = 0; x < chunkMap[y].size(); x++)
        {
            chunkMap[y][x] = Chunk({x,y});
        }
    }
    
    Chunk::initAllChunks(chunkMap);    
}

template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
ObjectOrganizer<MAP_SIZE_X, MAP_SIZE_Y>::ObjectOrganizer()
{
    m_initChunkMap();
}

template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
ObjectOrganizer<MAP_SIZE_X, MAP_SIZE_Y>::ObjectOrganizer(std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> chunkMap)
    : chunkMap{chunkMap}
{
    m_initChunkMap();
}

