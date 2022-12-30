#ifndef CHUNK_MAP_OBJECT_ARRAY_COPY_H
#define CHUNK_MAP_OBJECT_ARRAY_COPY_H

#include "chunkMap.h"
#include "ant.h"

template <class T, std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
class ChunkMapObjectArraysCopy
{

private:
    static_assert(std::is_base_of<GenericObject, T>::value, "T must inherit from GenericObject");
    void m_initAsAntArrayMap(ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> &rChunkMap)
    {
        for (unsigned int y = 0; y < rChunkMap.map.size(); y++)
        {
            for (unsigned int x = 0; x < rChunkMap.map[y].size(); x++)
            {
                pObjectArrayMap[y][x] = &rChunkMap.map[y][x].antsArray;
            }
        }
    }
    void m_initAsPheromoneArrayMap(ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> &rChunkMap)
    {
        for (unsigned int y = 0; y < rChunkMap.map.size(); y++)
        {
            for (unsigned int x = 0; x < rChunkMap.map[y].size(); x++)
            {
                pObjectArrayMap[y][x] = &rChunkMap.map[y][x].pheromonesArray;
            }
        }
    }
public:
    ChunkObjectArray<T>  *pObjectArrayMap[MAP_SIZE_Y][MAP_SIZE_X] = {{nullptr}};

    ChunkMapObjectArraysCopy() = default;

    ChunkMapObjectArraysCopy(ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> *pAChunkMap)
    {
        if constexpr (std::is_same_v<T, Ant>)
            m_initAsAntArrayMap(*pAChunkMap);
        else if constexpr (std::is_same_v<T, Pheromone>)
            m_initAsPheromoneArrayMap(*pAChunkMap);
    }


};


#endif //CHUNK_MAP_OBJECT_ARRAY_COPY_H
