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
private:
/*
 * TODO: add a member variable in genericObject: m_indexInChunk so that m_findIndexInChunkOfAnt() won't be needed anymore
 *  Might prove to be quite a performance improvement
 */

    unsigned int m_findIndexInChunkOfAnt(unsigned int indexOfAnt)
    {
        return antController.findIndexInChunkOfObject(indexOfAnt);
    }

    void m_removeAntFromWorldChunk(unsigned int indexOfAnt)
    {
        antController.removeObjectFromWorldChunk(indexOfAnt);
    }


    void m_insertAntsIntoWorldChunk(unsigned int indexOfAnt)
    {
        antController.insertObjectIntoWorldChunk(indexOfAnt);
    }
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


    //needs to be called only once after every objectHolder.insertAllNewObjectsIntoHolder() call
    void insertAntHolderIntoWorldChunks()
    {
        antController.insertObjectHolderIntoWorldChunks();
    }

    void moveAntAtIndexTo(unsigned int index, sf::Vector2f newPosition)
    {
        antController.moveObjectAtIndexTo(index, newPosition);
    }

    void moveAntAtIndexBy(unsigned int index, sf::Vector2f positionOffset)
    {
        antController.moveObjectAtIndexBy(index, positionOffset);
    }


};


#endif