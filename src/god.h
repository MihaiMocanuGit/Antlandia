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

///class responsible for creating map, it controls the structure logic and further calls
template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
class God
{
private:

    unsigned int m_findIndexInChunkOfAnt(unsigned int indexOfAnt)
    {
        Ant *pCurrentAnt = &ants.inUseObjects[indexOfAnt];
        sf::Vector2u antMapIndex = chunkMap.identifyMapIndexFromPosition(pCurrentAnt->getPosition());

        for (unsigned int i = 0; i < chunkMap.map[antMapIndex.y][antMapIndex.x].MAX_ANTS_CHUNK; ++i)
        {
            if (chunkMap.map[antMapIndex.y][antMapIndex.x].antsInChunk[i] == pCurrentAnt)
                return i;
        }
        return -1;
    }


    void m_removeAntFromWorldChunk(unsigned int indexOfAnt)
    {
        Ant *pCurrentAnt = &ants.inUseObjects[indexOfAnt];

        sf::Vector2u antMapIndex = chunkMap.identifyMapIndexFromPosition(pCurrentAnt->getPosition());
        unsigned int indexInChunk = m_findIndexInChunkOfAnt(indexOfAnt);

        chunkMap.map[antMapIndex.y][antMapIndex.x].antsInChunk[indexInChunk] = nullptr;
        chunkMap.map[antMapIndex.y][antMapIndex.x].noOfAnts--;

        pCurrentAnt->setPtrHomeChunk(nullptr);
    }

    void m_insertAntIntoWorldChunk(unsigned int indexOfAnt)
    {
        /*
         * We are searching through the array for the first empty spot. The array is not sorted, so it will have
         * empty spots inside itself.
         * When such a spot is found, we put our ant into it and increment the ants in chunk counter
         */
        Ant *pCurrentAnt = &ants.inUseObjects[indexOfAnt];
        sf::Vector2u antMapIndex = chunkMap.identifyMapIndexFromPosition(pCurrentAnt->getPosition());

        if (Chunk::MAX_ANTS_CHUNK <= chunkMap.map[antMapIndex.y][antMapIndex.x].noOfAnts)
            throw std::out_of_range("Chunk is already full");

        for (unsigned int i = 0; i < chunkMap.map[antMapIndex.y][antMapIndex.x].MAX_ANTS_CHUNK; ++i)
        {
            if (chunkMap.map[antMapIndex.y][antMapIndex.x].antsInChunk[i] == nullptr)
            {
                chunkMap.map[antMapIndex.y][antMapIndex.x].antsInChunk[i] = pCurrentAnt;
                chunkMap.map[antMapIndex.y][antMapIndex.x].noOfAnts++;

                pCurrentAnt->setPtrHomeChunk(&chunkMap.map[antMapIndex.y][antMapIndex.x]);

                return;
            }
        }
    }

public:

    std::size_t NO_OF_CHUNKS_X = MAP_SIZE_X;
    std::size_t NO_OF_CHUNKS_Y = MAP_SIZE_Y;

    ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> chunkMap;
    ObjectHolder<Ant> ants{Chunk::MAX_ANTS_CHUNK * MAP_SIZE_X * MAP_SIZE_Y};
    ObjectHolder<GenericObject> genericObjects{Chunk::MAX_ANTS_CHUNK * MAP_SIZE_X * MAP_SIZE_Y};


    //needs to be called only once after every objectHolder.insertAllNewObjectsIntoHolder() call
    void insertAntHolderIntoWorldChunks()
    {
        for (unsigned int i = 0; i < ants.inUseObjects.size(); ++i)
        {
            m_insertAntIntoWorldChunk(i);
        }
    }

    void moveAntAtIndexTo(unsigned int index, sf::Vector2f newPosition)
    {
        if (chunkMap.objectPositionFitsMap(newPosition))
        {
            Ant *pCurrentAnt = &ants.inUseObjects[index];
            sf::Vector2u currentChunkIndex = chunkMap.identifyMapIndexFromPosition(pCurrentAnt->getPosition());
            sf::Vector2u newChunkIndex = chunkMap.identifyMapIndexFromPosition(newPosition);

            if (currentChunkIndex == newChunkIndex)
            {
                pCurrentAnt->setPosition(newPosition);
            } else
            {
                m_removeAntFromWorldChunk(index);
                pCurrentAnt->setPosition(newPosition);
                m_insertAntIntoWorldChunk(index);

            }
        }
    }

    void moveAntAtIndexBy(unsigned int index, sf::Vector2f positionOffset)
    {
        moveAntAtIndexTo(index, ants.inUseObjects[index].getPosition() + positionOffset);
    }


};


#endif