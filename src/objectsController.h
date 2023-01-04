#ifndef OBJECTS_CONTROLLER_H
#define OBJECTS_CONTROLLER_H

#include "objectHolder.h"
#include "chunk.h"
#include "chunkMap.h"
#include "chunkMapObjectArrayCopy.h"
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
class ObjectsController
{
    static_assert(std::is_base_of<GenericObject, T>::value, "T must inherit from GenericObject");
private:
    unsigned int m_lastKnownFreeSpace = 0;

    void m_erase_if(std::vector<T> &rObjects, bool (*p)(const T&))
    {
        auto first = rObjects.begin();
        auto last = rObjects.end();
        //https://en.cppreference.com/w/cpp/algorithm/remove
        first = std::find_if(first, last, p);
        if (first != last)
            for (auto i = first; ++i != last;)
                if (!p(*i))
                {
                    //m_removeObjectFromWorldChunk((*first).getIndexInHolder());
                    *first++ = std::move(*i);
                }

        //https://en.cppreference.com/w/cpp/container/vector/erase2
        //auto r = std::distance(first, last);

        for(auto it = first; it < last; it++)
            m_removeObjectFromWorldChunk((*it).getIndexInHolder());
        rObjects.erase(first, last);

        //return r;
    }

public:
    static constexpr std::size_t NO_OF_CHUNKS_X = MAP_SIZE_X;
    static constexpr std::size_t NO_OF_CHUNKS_Y = MAP_SIZE_Y;

    static constexpr unsigned int INIT_AS_GENERIC_OBJECTS = 0;
    static constexpr unsigned int INIT_AS_ANTS = 1;
    static constexpr unsigned int INIT_AS_PHEROMONES = 2;

    ObjectHolder<T> objectHolder;
    ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> *pChunkMap = nullptr;

    ChunkMapObjectArraysCopy<T, MAP_SIZE_X, MAP_SIZE_Y> chunkMapObjectArrays;

    ObjectsController() = default;
    explicit ObjectsController(ChunkMap<MAP_SIZE_X, MAP_SIZE_Y> *pAChunkMap) : pChunkMap{pAChunkMap}
    {
        chunkMapObjectArrays = ChunkMapObjectArraysCopy<T, MAP_SIZE_X, MAP_SIZE_Y>(pAChunkMap);
    }

    /*
     * TODO: add a member variable in genericObject: m_indexInChunk so that m_findIndexInChunkOfObject() won't be needed anymore
     *  Might prove quite a performance improvement
     */
    unsigned int m_findIndexInChunkOfObject(unsigned int indexOfObject)
    {
        T *pCurrentObject = &objectHolder.inUseObjects[indexOfObject];
        sf::Vector2u objectMapIndex = pChunkMap->identifyMapIndexFromPosition(pCurrentObject->getPosition());
        ChunkObjectArray<T> *pCurrentChunkArray = chunkMapObjectArrays.pObjectArrayMap[objectMapIndex.y][objectMapIndex.x];

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
        ChunkObjectArray<T> *pCurrentChunkArray = chunkMapObjectArrays.pObjectArrayMap[objectMapIndex.y][objectMapIndex.x];

        pCurrentChunkArray->objectsInChunk[indexInChunk] = nullptr;
        pCurrentChunkArray->noOfObjects--;

        pCurrentObject->setPtrHomeChunk(nullptr);
        //forgot to differentiate between chunks
        if (indexInChunk < m_lastKnownFreeSpace) m_lastKnownFreeSpace = indexInChunk;
    }


    //needs to be called only once after every objectHolder.moveAllNewObjectsIntoHolder() call
    void insertObjectHolderIntoWorldChunks()
    {
        for (unsigned int i = 0; i < objectHolder.inUseObjects.size(); ++i)
        {
            insertObjectIntoWorldChunk(i);
        }
    }

    void insertObjectIntoWorldChunk(unsigned int indexInHolder)
    {
        /*
        * We are searching through the array for the first empty spot. The array is not sorted, so it will have
        * empty spots inside itself.
        * When such a spot is found, we put our object into it and increment the objects in chunk counter
        */
        T *pCurrentObject = &objectHolder.inUseObjects[indexInHolder];
        sf::Vector2u objectMapIndex = pChunkMap->identifyMapIndexFromPosition(pCurrentObject->getPosition());

        ChunkObjectArray<T> *pCurrentChunkArray = chunkMapObjectArrays.pObjectArrayMap[objectMapIndex.y][objectMapIndex.x];
        if (Chunk::MAX_OBJECTS_PER_TYPE <= pCurrentChunkArray->noOfObjects)
            throw std::out_of_range("Chunk is already full");

        /*
         * TODO: We can remember the last found free space (which was later occupied), saving some cpu time
         *  so i = m_lastKnownFreeSpace instead of i = 0
         */

        for (unsigned int i = 0; i < pCurrentChunkArray->MAX_OBJECTS_PER_TYPE; ++i)
        {
            if (pCurrentChunkArray->objectsInChunk[i] == nullptr)
            {
                pCurrentChunkArray->objectsInChunk[i] = pCurrentObject;
                pCurrentChunkArray->noOfObjects++;

                pCurrentObject->setPtrHomeChunk(&pChunkMap->map[objectMapIndex.y][objectMapIndex.x]);

                m_lastKnownFreeSpace = i;
                return;
            }
        }
    }


    void removeDeadObjects()
    {
        m_erase_if(objectHolder.inUseObjects, [](const T &x){ return x.isDead; });
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
                insertObjectIntoWorldChunk(index);

            }
        }
    }

    void moveObjectAtIndexBy(unsigned int index, sf::Vector2f positionOffset)
    {
        moveObjectAtIndexTo(index, objectHolder.inUseObjects[index].getPosition() + positionOffset);
    }

    ///
    /// \tparam DischargedT
    /// \param indexParent
    /// \param rDischargedObject It will always inherit the ant's position
    /// \param rDischargedObjCntrl It is assumed that MAP_SIZE_X/Y is the same for both the parent's controller
    /// and discharged objects's controller
    /// \return The index in DischargedT type holder
    template <class DischargedT>
    unsigned int dischargeObjectFromParentAtIndex(unsigned int indexParent, DischargedT &rDischargedObject,
                                          ObjectsController<DischargedT, MAP_SIZE_X, MAP_SIZE_Y> &rDischargedObjCntrl)
    {
        static_assert(std::is_base_of<GenericObject, DischargedT>::value, "DischargedT must inherit from GenericObject");
        //inherit the ant's position
        rDischargedObject.setPosition(objectHolder.inUseObjects[indexParent].getPosition());

        rDischargedObjCntrl.objectHolder.insertGivenObjectIntoHolder(rDischargedObject);

        try
        {
            rDischargedObjCntrl.insertObjectIntoWorldChunk(rDischargedObject.getIndexInHolder());
        }
        catch (const std::exception& e)
        {
            //std::cout << e.what();

            auto pVector =  &rDischargedObjCntrl.objectHolder.inUseObjects;
            unsigned int index = rDischargedObject.getIndexInHolder();
            pVector->erase(pVector->begin() + index);
        }

        return rDischargedObject.getIndexInHolder();
    }

};


#endif //OBJECTS_CONTROLLER_H
