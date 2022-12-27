#ifndef OBJECT_ORGANIZER_H
#define OBJECT_ORGANIZER_H

#include <array>
#include <stdexcept>
#include <iostream>

#include "chunk.h"
#include "ant.h"
#include "genericObject.h"
#include "objectHolder.h"
#include "chunkMap.h"
#include "objectsController.h"

///class responsible for creating map, it controls the structure logic and further calls
template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
class World
{
/*
 * TODO: add a member variable in genericObject: m_indexInChunk so that m_findIndexInChunkOfAnt() won't be needed anymore
 *  Might prove to be quite a performance improvement
 */

public:

    static constexpr std::size_t NO_OF_CHUNKS_X = MAP_SIZE_X;
    static constexpr std::size_t NO_OF_CHUNKS_Y = MAP_SIZE_Y;

    ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> chunkMap;

    ObjectsController<Ant, MAP_SIZE_X, MAP_SIZE_Y> antController;
    ObjectsController<Pheromone, MAP_SIZE_X, MAP_SIZE_Y> pheromoneController;

    World()
    {
        antController = ObjectsController<Ant, MAP_SIZE_X, MAP_SIZE_Y>(&chunkMap);
    }

};


#endif