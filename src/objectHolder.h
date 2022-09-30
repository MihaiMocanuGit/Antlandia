#ifndef OBJECT_HOLDER_H
#define OBJECT_HOLDER_H

#include <vector>

#include "chunk.h"



template<class T>
class ObjectHolder
{
private:
        
        unsigned int m_RESERVED_VECTOR_SPACE;

public:

        //all initialized objects are in here
        std::vector<T> inUseObjects;

        //is a temporal holding place where new objects are waiting to be initialized, after they were initialized call insertAllNewObjectsIntoHolder()
        //so that all new objects are sent to inUseObjects
        std::vector<T> newObjects;

        ObjectHolder()
        {
                //we make the assumption that the chunk map is 10 by 10 and one chunk can hold at most Chunk::MAX_ANTS_CHUNK
                changeReservedVectorSpace(Chunk::MAX_ANTS_CHUNK * 10 * 10);
        }

        //best value Chunk::MAX_ANTS_CHUNK * ObjectOrganizer.noOfChunksX * ObjectOrganizer.noOfChunksY
        ObjectHolder(std::size_t aproximateVectorSize)
        {
                changeReservedVectorSpace(aproximateVectorSize);
        }



        //creates new objects which have to be manually initialized by user right after.
        void createNewObjects(unsigned int noOfObjects)
        {
                for(unsigned int i = 0; i < noOfObjects; i++)
                        newObjects.push_back(T());
        }

        //don't forget to manually init objects before; 
        void insertAllNewObjectsIntoHolder()
        {
                for(unsigned int i = newObjects.size() - 1; i > 0; i++)
                {
                        inUseObjects.push_back(newObjects[i]);
                        newObjects.pop_back();
                }
        }

        //best value Chunk::MAX_ANTS_CHUNK * ObjectOrganizer.noOfChunksX * ObjectOrganizer.noOfChunksY
        void changeReservedVectorSpace(std::size_t newReservedSpace)
        {
                ObjectHolder::m_RESERVED_VECTOR_SPACE = newReservedSpace;
                inUseObjects.reserve(newReservedSpace);
                newObjects.reserve(newReservedSpace);
        }
};


#endif