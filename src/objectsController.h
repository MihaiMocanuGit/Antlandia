#ifndef OBJECTS_CONTROLLER_H
#define OBJECTS_CONTROLLER_H

#include "objectHolder.h"
#include "chunk.h"
#include "chunkMap.h"

template <class T, std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
class ObjectsChunkArrayCopy
{
public:
    std::array<T*, Chunk::MAX_ANTS_CHUNK> *pArrayMap[MAP_SIZE_Y][MAP_SIZE_X];

    void initAsAntArrayMap(const ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> &rChunkMap)
    {
        std::array<T*, Chunk::MAX_ANTS_CHUNK> *pAntArrayMap[MAP_SIZE_Y][MAP_SIZE_X];
        for (unsigned int y = 0; y < rChunkMap.size(); y++)
        {
            for (unsigned int x = 0; x < rChunkMap[y].size(); x++)
            {
                pArrayMap[y][x] = &rChunkMap[y][x].antsInChunk();
            }
        }
    }
    static void initAsPheromoneArrayMap(const ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> pChunkMap);
};

template <class T, std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
class ObjectsController
{
/*
 * TODO: Modify all apparitions of "ant" into "object" / "obj"
 */
private:
    /*
 * TODO: add a member variable in genericObject: m_indexInChunk so that m_findIndexInChunkOfAnt() won't be needed anymore
 *  Might prove quite a performance improvement
 */
    unsigned int m_findIndexInChunkOfAnt(unsigned int indexOfAnt)
    {
        Ant *pCurrentAnt = &objectHolder.inUseObjects[indexOfAnt];
        sf::Vector2u antMapIndex = pChunkMapCopy->identifyMapIndexFromPosition(pCurrentAnt->getPosition());

        for (unsigned int i = 0; i < pChunkMapCopy->map[antMapIndex.y][antMapIndex.x].MAX_ANTS_CHUNK; ++i)
        {
            if (pChunkMapCopy->map[antMapIndex.y][antMapIndex.x].antsInChunk[i] == pCurrentAnt)
                return i;
        }
        return -1;
    }


    void m_removeAntFromWorldChunk(unsigned int indexOfAnt)
    {
        Ant *pCurrentAnt = &objectHolder.inUseObjects[indexOfAnt];

        sf::Vector2u antMapIndex = pChunkMapCopy->identifyMapIndexFromPosition(pCurrentAnt->getPosition());
        unsigned int indexInChunk = m_findIndexInChunkOfAnt(indexOfAnt);

        chunkArrayCopy.pArrayMap[antMapIndex.y][antMapIndex.x].antsInChunk[indexInChunk] = nullptr;
        chunkArrayCopy.pArrayMap[antMapIndex.y][antMapIndex.x].noOfAnts--;

        pCurrentAnt->setPtrHomeChunk(nullptr);
    }

    void m_insertAntIntoWorldChunk(unsigned int indexOfAnt)
    {
        /*
         * We are searching through the array for the first empty spot. The array is not sorted, so it will have
         * empty spots inside itself.
         * When such a spot is found, we put our ant into it and increment the ants in chunk counter
         */
        Ant *pCurrentAnt = &objectHolder.inUseObjects[indexOfAnt];
        sf::Vector2u antMapIndex = pChunkMapCopy.identifyMapIndexFromPosition(pCurrentAnt->getPosition());

        if (Chunk::MAX_ANTS_CHUNK <= pChunkMapCopy.map[antMapIndex.y][antMapIndex.x].noOfAnts)
            throw std::out_of_range("Chunk is already full");

        for (unsigned int i = 0; i < pChunkMapCopy.map[antMapIndex.y][antMapIndex.x].MAX_ANTS_CHUNK; ++i)
        {
            if (pChunkMapCopy->map[antMapIndex.y][antMapIndex.x].antsInChunk[i] == nullptr)
            {
                pChunkMapCopy->map[antMapIndex.y][antMapIndex.x].antsInChunk[i] = pCurrentAnt;
                pChunkMapCopy->map[antMapIndex.y][antMapIndex.x].noOfAnts++;

                pCurrentAnt->setPtrHomeChunk(&pChunkMapCopy.map[antMapIndex.y][antMapIndex.x]);

                return;
            }
        }
    }

public:
    static constexpr std::size_t NO_OF_CHUNKS_X = MAP_SIZE_X;
    static constexpr std::size_t NO_OF_CHUNKS_Y = MAP_SIZE_Y;

    static constexpr unsigned int INIT_AS_ANTS = 0;
    static constexpr unsigned int INIT_AS_PHEROMONES = 1;

    ObjectHolder<T> objectHolder{Chunk::MAX_ANTS_CHUNK * MAP_SIZE_X * MAP_SIZE_Y / 4};
    ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> *pChunkMapCopy;

    ObjectsChunkArrayCopy<T, MAP_SIZE_X, MAP_SIZE_Y> chunkArrayCopy;

    ObjectsController(ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> *pChunkMap, unsigned int init_option = 100) : pChunkMapCopy(pChunkMap)
    {
        switch (init_option)
        {
            case INIT_AS_ANTS:
                chunkArrayCopy.initAsAntArrayMap();
                break;
            case INIT_AS_PHEROMONES:
                chunkArrayCopy.initAsPheromoneArrayMap();
                break;
            default:
                throw std::invalid_argument("invalid init_option");
        }
    }


    //needs to be called only once after every objectHolder.insertAllNewObjectsIntoHolder() call
    void insertAntHolderIntoWorldChunks()
    {
        for (unsigned int i = 0; i < objectHolder.inUseObjects.size(); ++i)
        {
            m_insertAntIntoWorldChunk(i);
        }
    }

    void moveAntAtIndexTo(unsigned int index, sf::Vector2f newPosition)
    {
        if (pChunkMapCopy->objectPositionFitsMap(newPosition))
        {
            Ant *pCurrentAnt = &objectHolder.inUseObjects[index];
            sf::Vector2u currentChunkIndex = pChunkMapCopy->identifyMapIndexFromPosition(pCurrentAnt->getPosition());
            sf::Vector2u newChunkIndex = pChunkMapCopy->identifyMapIndexFromPosition(newPosition);

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
        moveAntAtIndexTo(index, objectHolder.inUseObjects[index].getPosition() + positionOffset);
    }
};


#endif //OBJECTS_CONTROLLER_H
