#ifndef OBJECT_HOLDER_H
#define OBJECT_HOLDER_H

#include <vector>



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

        ObjectHolder();
        //best value Chunk::MAX_ANTS_CHUNK * ObjectOrganizer.noOfChunksX * ObjectOrganizer.noOfChunksY
        ObjectHolder(std::size_t aproximateVectorSize);


        //creates new objects which have to be manually initialized by user right after.
        void createNewObjects(unsigned int noOfObjects);

        //don't forget to manually init objects before; 
        void insertAllNewObjectsIntoHolder();

        //best value Chunk::MAX_ANTS_CHUNK * ObjectOrganizer.noOfChunksX * ObjectOrganizer.noOfChunksY
        void changeReservedVectorSpace(std::size_t newReservedSpace);
};


#endif