#ifndef OBJECT_HOLDER_H
#define OBJECT_HOLDER_H

#include <vector>



template<class T>
class ObjectHolder
{
private:
        
        unsigned int m_RESERVED_VECTOR_SPACE = -1;
public:

        //all initialized objects are in here
        std::vector<T> inUseObjects;

        //is a temporal holding place where new objects are waiting to be initialized, after they were initialized call insertAllNewObjectsIntoHolder()
        //so that all new objects are sent to inUseObjects
        std::vector<T> newObjects;

        ObjectHolder()
        {
                //we make the assumption that the chunk map is 10 by 10 and one chunk can hold at most Chunk::MAX_ANTS_CHUNK
                //changeReservedVectorSpace(Chunk::MAX_ANTS_CHUNK * 10 * 10);
        }

        //best value Chunk::MAX_ANTS_CHUNK * ObjectOrganizer.noOfChunksX * ObjectOrganizer.noOfChunksY
        ObjectHolder(std::size_t aproximateVectorSize)
        {
                //changeReservedVectorSpace(aproximateVectorSize);
        }



        //creates new objects which have to be manually initialized by user right after.
        void createNewObjects(unsigned int noOfObjects)
        {
                newObjects.resize(newObjects.size() + noOfObjects);
        }

        //don't forget to manually init objects before;
        //Note: this doesn't actually insert the objects into map
        void insertAllNewObjectsIntoHolder()
        {
                inUseObjects.insert(inUseObjects.end(), newObjects.begin(), newObjects.end());
                newObjects.clear();           
        }


        //best value Chunk::MAX_ANTS_CHUNK * ObjectOrganizer.noOfChunksX * ObjectOrganizer.noOfChunksY
        void changeReservedVectorSpace(std::size_t newReservedSpace)
        {
                m_RESERVED_VECTOR_SPACE = newReservedSpace;
                inUseObjects.reserve(newReservedSpace);
                newObjects.reserve(newReservedSpace);
        }
};


#endif