#ifndef OBJECTS_CONTROLLER_H
#define OBJECTS_CONTROLLER_H

#include "objectHolder.h"
#include "chunk.h"
#include "chunkMap.h"

/*
 * Layer structure:
 *      World - ObjectController templates  |\|\ Object -
 *      ChunkMap                            \|\| - Chunk -
 *      Chunks - Objects arrays template    |\|\ - ArrayCopy
 *
 *  ObjectController uses ObjectChunkArraysCopy to create a bridge between Object Controllers template instances
 *  and Object Arrays from every chunk by copying all needed references.
 */
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
    ObjectChunkArray<T>  *pObjectArrayMap[MAP_SIZE_Y][MAP_SIZE_X];

    ChunkMapObjectArraysCopy() = default;

    ChunkMapObjectArraysCopy(ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> *pAChunkMap)
    {
        if constexpr (std::is_same_v<T, Ant>)
            m_initAsAntArrayMap(*pAChunkMap);
        else if constexpr (std::is_same_v<T, Pheromone>)
            m_initAsPheromoneArrayMap(*pAChunkMap);
    }


};

template <class T, std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
class ObjectsController
{
    static_assert(std::is_base_of<GenericObject, T>::value, "T must inherit from GenericObject");
/*
 * TODO: Modify all apparitions of "ant" into "object" / "obj"
 */
public:
    /*
     * TODO: Had to modify private: to public: for implementation testing,
     *  Remember to change it back/modify the structure accordingly
     *
     * TODO: add a member variable in genericObject: m_indexInChunk so that m_findIndexInChunkOfObject() won't be needed anymore
     *  Might prove quite a performance improvement
     */
    unsigned int m_findIndexInChunkOfObject(unsigned int indexOfObject)
    {
        T *pCurrentObject = &objectHolder.inUseObjects[indexOfObject];
        sf::Vector2u objectMapIndex = pChunkMap->identifyMapIndexFromPosition(pCurrentObject->getPosition());
        ObjectChunkArray<T> *pCurrentChunkArray = chunkMapObjectArrays.pObjectArrayMap[objectMapIndex.y][objectMapIndex.x];

        for (unsigned int i = 0; i < pCurrentChunkArray->MAX_OBJECTS_PER_TYPE; ++i)
        {
            if (pCurrentChunkArray->objectsInChunk[i] == pCurrentObject)
                return i;
        }
        return -1;
    }


    void m_removeObjectFromWorldChunk(unsigned int indexOfObject)
    {
        T *pCurrentObject = &objectHolder.inUseObjects[indexOfObject];

        sf::Vector2u objectMapIndex = pChunkMap->identifyMapIndexFromPosition(pCurrentObject->getPosition());
        unsigned int indexInChunk = m_findIndexInChunkOfObject(indexOfObject);
        ObjectChunkArray<T> *pCurrentChunkArray = chunkMapObjectArrays.pObjectArrayMap[objectMapIndex.y][objectMapIndex.x];

        pCurrentChunkArray->objectsInChunk[indexInChunk] = nullptr;
        pCurrentChunkArray->noOfObjects--;

        pCurrentObject->setPtrHomeChunk(nullptr);
    }

    void m_insertObjectIntoWorldChunk(unsigned int indexOfObject)
    {
        /*
         * We are searching through the array for the first empty spot. The array is not sorted, so it will have
         * empty spots inside itself.
         * When such a spot is found, we put our object into it and increment the objects in chunk counter
         */
        T *pCurrentObject = &objectHolder.inUseObjects[indexOfObject];
        sf::Vector2u objectMapIndex = pChunkMap->identifyMapIndexFromPosition(pCurrentObject->getPosition());

        ObjectChunkArray<T> *pCurrentChunkArray = chunkMapObjectArrays.pObjectArrayMap[objectMapIndex.y][objectMapIndex.x];
        if (Chunk::MAX_OBJECTS_PER_TYPE <= pCurrentChunkArray->noOfObjects)
            throw std::out_of_range("Chunk is already full");

        /*
         * TODO: We can remember the last found free space (which was later occupied), saving some cpu time
         *  so i = lastKnownFreeSpace instead of i = 0
         */
        for (unsigned int i = 0; i < pCurrentChunkArray->MAX_OBJECTS_PER_TYPE; ++i)
        {
            if (pCurrentChunkArray->objectsInChunk[i] == nullptr)
            {
                pCurrentChunkArray->objectsInChunk[i] = pCurrentObject;
                pCurrentChunkArray->noOfObjects++;

                pCurrentObject->setPtrHomeChunk(&pChunkMap->map[objectMapIndex.y][objectMapIndex.x]);

                return;
            }
        }
    }

public:
    static constexpr std::size_t NO_OF_CHUNKS_X = MAP_SIZE_X;
    static constexpr std::size_t NO_OF_CHUNKS_Y = MAP_SIZE_Y;

    static constexpr unsigned int INIT_AS_GENERIC_OBJECTS = 0;
    static constexpr unsigned int INIT_AS_ANTS = 1;
    static constexpr unsigned int INIT_AS_PHEROMONES = 2;

    ObjectHolder<T> objectHolder{Chunk::MAX_OBJECTS_PER_TYPE * MAP_SIZE_X * MAP_SIZE_Y / 4};
    ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> *pChunkMap;

    ChunkMapObjectArraysCopy<T, MAP_SIZE_X, MAP_SIZE_Y> chunkMapObjectArrays;

    ObjectsController() = default;
    ObjectsController(ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> *pAChunkMap) : pChunkMap{pAChunkMap}
    {
        chunkMapObjectArrays = ChunkMapObjectArraysCopy<T, MAP_SIZE_X, MAP_SIZE_Y>(pAChunkMap);
    }


    //needs to be called only once after every objectHolder.insertAllNewObjectsIntoHolder() call
    void insertObjectHolderIntoWorldChunks()
    {
        for (unsigned int i = 0; i < objectHolder.inUseObjects.size(); ++i)
        {
            m_insertObjectIntoWorldChunk(i);
        }
    }

    void moveObjectAtIndexTo(unsigned int index, sf::Vector2f newPosition)
    {
        if (pChunkMap->objectPositionFitsMap(newPosition))
        {
            T *pCurrentObject = &objectHolder.inUseObjects[index];
            sf::Vector2u currentChunkIndex = pChunkMap->identifyMapIndexFromPosition(pCurrentObject->getPosition());
            sf::Vector2u newChunkIndex = pChunkMap->identifyMapIndexFromPosition(newPosition);

            if (currentChunkIndex == newChunkIndex)
            {
                pCurrentObject->setPosition(newPosition);
            } else
            {
                m_removeObjectFromWorldChunk(index);
                pCurrentObject->setPosition(newPosition);
                m_insertObjectIntoWorldChunk(index);

            }
        }
    }

    void moveObjectAtIndexBy(unsigned int index, sf::Vector2f positionOffset)
    {
        moveObjectAtIndexTo(index, objectHolder.inUseObjects[index].getPosition() + positionOffset);
    }
};


#endif //OBJECTS_CONTROLLER_H
