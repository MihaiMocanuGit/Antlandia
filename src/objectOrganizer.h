#ifndef OBJECT_ORGANIZER_H
#define OBJECT_ORGANIZER_H

#include <array>
#include <stdexcept>
#include <iostream>

#include "chunk.h"
#include "ant.h"
#include "genericObject.h"
#include "objectHolder.h"


///class responsible for creating chunkMap, it controls the structure logic and further calls
template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
class ObjectOrganizer
{
private:

    bool m_objectPositionFitsChunkMap(const sf::Vector2f &position)
    {

        if (position.x >= 0 and position.y >= 0)
            if (position.x <= Chunk::CHUNK_SIZE.x * MAP_SIZE_X and position.y <= Chunk::CHUNK_SIZE.y * MAP_SIZE_Y)
                return true;
            else
                return false;
        else
            return false;
    }

    //create chunk map and inits all chunks
    void m_initChunkMap()
    {
        for (unsigned int y = 0; y < chunkMap.size(); y++)
        {
            for (unsigned int x = 0; x < chunkMap[y].size(); x++)
            {
                chunkMap[y][x] = Chunk({x, y});
            }
        }
        Chunk::initAllChunks(chunkMap);
    }

    sf::Vector2u m_identifyChunkMapIndexFromPosition(const sf::Vector2f &position)
    {
        if (m_objectPositionFitsChunkMap(position))
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
            throw std::domain_error("object position doesn't fit into chunkMap");
        }
    }

    unsigned int m_findIndexInChunkOfAnt(unsigned int indexOfAnt)
    {
        /*
         * This can be improved by taking into consideration that antsInChunk[i] is an array
         * We are comparing memory locations, so instead of iterating through the array, by knowing the size of the array
         * we can calculate the index just by
         * index = (pCurrentAnt - &antsInChunk[0]) / sizeof(Ant)
         * and 0 <= index <= noOfAnts
         */
        Ant *pCurrentAnt = &ants.inUseObjects[indexOfAnt];
        sf::Vector2u antMapIndex = m_identifyChunkMapIndexFromPosition(pCurrentAnt->getPosition());

        for (unsigned int i = 0; i < chunkMap[antMapIndex.y][antMapIndex.x].MAX_ANTS_CHUNK; ++i)
        {
            if (chunkMap[antMapIndex.y][antMapIndex.x].antsInChunk[i] == pCurrentAnt)
                return i;
        }
        return -1;
    }

    void m_removeAntFromWorldChunk(unsigned int indexOfAnt)
    {
        Ant *pCurrentAnt = &ants.inUseObjects[indexOfAnt];

        sf::Vector2u antMapIndex = m_identifyChunkMapIndexFromPosition(pCurrentAnt->getPosition());
        unsigned int indexInChunk = m_findIndexInChunkOfAnt(indexOfAnt);

        chunkMap[antMapIndex.y][antMapIndex.x].antsInChunk[indexInChunk] = nullptr;
        chunkMap[antMapIndex.y][antMapIndex.x].noOfAnts--;

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
        sf::Vector2u antMapIndex = m_identifyChunkMapIndexFromPosition(pCurrentAnt->getPosition());

        if (Chunk::MAX_ANTS_CHUNK <= chunkMap[antMapIndex.y][antMapIndex.x].noOfAnts)
            throw std::out_of_range("Chunk is already full");

        for (unsigned int i = 0; i < chunkMap[antMapIndex.y][antMapIndex.x].MAX_ANTS_CHUNK; ++i)
        {
            if (chunkMap[antMapIndex.y][antMapIndex.x].antsInChunk[i] == nullptr)
            {
                chunkMap[antMapIndex.y][antMapIndex.x].antsInChunk[i] = pCurrentAnt;
                chunkMap[antMapIndex.y][antMapIndex.x].noOfAnts++;

                pCurrentAnt->setPtrHomeChunk((void *) &chunkMap[antMapIndex.y][antMapIndex.x]);

                return;
            }
        }
    }

public:

    static constexpr std::size_t noOfChunksX = MAP_SIZE_X;
    static constexpr std::size_t noOfChunksY = MAP_SIZE_Y;

    ObjectHolder<Ant> ants{Chunk::MAX_ANTS_CHUNK * noOfChunksX * noOfChunksY};
    //ObjectHolder<GenericObject> genericObjects{Chunk::MAX_ANTS_CHUNK * noOfChunksX * noOfChunksY};


    std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> chunkMap;

    ObjectOrganizer()
    {

        m_initChunkMap();
    }

    //needs to be called only once after every objectHolder.insertAllNewObjectsIntoHolder() call
    void insertAntHolderIntoWorldChunks()
    {
        for (unsigned int i = 0; i < ants.inUseObjects.size(); ++i)
        {
            m_insertAntIntoWorldChunk(i);
        }
    }

    //NOTE, WRITTEN THIS WHILE DRUNK, MUST RECHECK WHEN SOBER
    void moveAntAtIndexTo(unsigned int index, sf::Vector2f newPosition)
    {
        if (m_objectPositionFitsChunkMap(newPosition))
        {
            Ant *pCurrentAnt = &ants.inUseObjects[index];
            sf::Vector2u currentChunkIndex = m_identifyChunkMapIndexFromPosition(pCurrentAnt->getPosition());
            sf::Vector2u newChunkIndex = m_identifyChunkMapIndexFromPosition(newPosition);

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