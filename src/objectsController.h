#ifndef OBJECTS_CONTROLLER_H
#define OBJECTS_CONTROLLER_H

#include "objectHolder.h"
#include "chunk.h"
#include "chunkMap.h"

/*
 * Layer structure:
 *      World - ObjectController templates
 *      ChunkMap
 *      Chunks - Objects arrays template
 *
 *  ObjectController uses ObjectChunkArraysCopy to create a bridge between Object Controllers template instances
 *  and Object Arrays from every chunk by copying all needed references.
 */
template <class T, std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
class ObjectChunkArraysCopy
{
    static_assert(std::is_base_of<GenericObject, T>::value, "T must inherit from GenericObject");
public:
    std::array<T*, Chunk::MAX_ANTS_CHUNK> *pArrayMap[MAP_SIZE_Y][MAP_SIZE_X];

    void initAsAntArrayMap(const ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> &rChunkMap)
    {
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
    static_assert(std::is_base_of<GenericObject, T>::value, "T must inherit from GenericObject");
/*
 * TODO: Modify all apparitions of "ant" into "object" / "obj"
 */
private:
    /*
 * TODO: add a member variable in genericObject: m_indexInChunk so that m_findIndexInChunkOfObject() won't be needed anymore
 *  Might prove quite a performance improvement
 */
    unsigned int m_findIndexInChunkOfObject(unsigned int indexOfObject)
    {
        T *pCurrentObject = &objectHolder.inUseObjects[indexOfObject];
        sf::Vector2u objectMapIndex = pChunkMap->identifyMapIndexFromPosition(pCurrentObject->getPosition());

        for (unsigned int i = 0; i < pChunkMap->map[objectMapIndex.y][objectMapIndex.x].MAX_ANTS_CHUNK; ++i)
        {
            if (pChunkMap->map[objectMapIndex.y][objectMapIndex.x].objectsInChunk[i] == pCurrentObject)
                return i;
        }
        return -1;
    }


    void m_removeObjectFromWorldChunk(unsigned int indexOfObject)
    {
        T *pCurrentObject = &objectHolder.inUseObjects[indexOfObject];

        sf::Vector2u objectMapIndex = pChunkMap->identifyMapIndexFromPosition(pCurrentObject->getPosition());
        unsigned int indexInChunk = m_findIndexInChunkOfObject(indexOfObject);

        chunkArraysCopy.pArrayMap[objectMapIndex.y][objectMapIndex.x].objectsInChunk[indexInChunk] = nullptr;
        chunkArraysCopy.pArrayMap[objectMapIndex.y][objectMapIndex.x].noOfObjects--;

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

        if (Chunk::MAX_ANTS_CHUNK <= pChunkMap->map[objectMapIndex.y][objectMapIndex.x].noOfObjects)
            throw std::out_of_range("Chunk is already full");

        for (unsigned int i = 0; i < pChunkMap->map[objectMapIndex.y][objectMapIndex.x].MAX_ANTS_CHUNK; ++i)
        {
            if (pChunkMap->map[objectMapIndex.y][objectMapIndex.x].objectsInChunk[i] == nullptr)
            {
                pChunkMap->map[objectMapIndex.y][objectMapIndex.x].objectsInChunk[i] = pCurrentObject;
                pChunkMap->map[objectMapIndex.y][objectMapIndex.x].noOfObjects++;

                pCurrentObject->setPtrHomeChunk(&pChunkMap->map[objectMapIndex.y][objectMapIndex.x]);

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
    ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> *pChunkMap;

    ObjectChunkArraysCopy<T, MAP_SIZE_X, MAP_SIZE_Y> chunkArraysCopy;

    ObjectsController(ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> *pChunkMap, unsigned int init_option = 100) : pChunkMap(pChunkMap)
    {
        switch (init_option)
        {
            case INIT_AS_ANTS:
                chunkArraysCopy.initAsObjectArrayMap();
                break;
            case INIT_AS_PHEROMONES:
                chunkArraysCopy.initAsPheromoneArrayMap();
                break;
            default:
                throw std::invalid_argument("invalid init_option");
        }
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
