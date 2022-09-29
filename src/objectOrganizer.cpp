#include "objectOrganizer.h"


template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y, std::size_t MAX_NO_OBJECTS_IN_GROUP>
void ObjectOrganizer<MAP_SIZE_X, MAP_SIZE_Y, MAX_NO_OBJECTS_IN_GROUP>::m_initChunkMap()
{
    for(unsigned int y = 0; y < m_chunkMap.size(); y++)
    {
        for(unsigned int x = 0; x < m_chunkMap[y].size(); x++)
        {
            m_chunkMap[y][x] = Chunk({x,y});
        }
    }
    
    Chunk::initAllChunks(m_chunkMap);    
}

template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y, std::size_t MAX_NO_OBJECTS_IN_GROUP>
ObjectOrganizer<MAP_SIZE_X, MAP_SIZE_Y, MAX_NO_OBJECTS_IN_GROUP>::ObjectOrganizer()
{

}

template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y, std::size_t MAX_NO_OBJECTS_IN_GROUP>
ObjectOrganizer<MAP_SIZE_X, MAP_SIZE_Y, MAX_NO_OBJECTS_IN_GROUP>::ObjectOrganizer(std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> chunkMap)
    : m_chunkMap{chunkMap}
{
    m_initChunkMap();
}