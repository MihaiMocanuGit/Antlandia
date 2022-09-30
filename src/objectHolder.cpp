#include "objectHolder.h"

/*
#include "chunk.h"

template<class T>
ObjectHolder<T>::ObjectHolder()
{
    //we make the assumption that the chunk map is 10 by 10 and one chunk can hold at most Chunk::MAX_ANTS_CHUNK
    changeReservedVectorSpace(Chunk::MAX_ANTS_CHUNK * 10 * 10);
}

template<class T>
ObjectHolder<T>::ObjectHolder(std::size_t aproximateVectorSize)
{
    changeReservedVectorSpace(aproximateVectorSize);
}



template<class T>
void ObjectHolder<T>::createNewObjects(unsigned int noOfObjects)
{
    for(unsigned int i = 0; i < noOfObjects; i++)
        newObjects.push_back(T());
}


template<class T>
void ObjectHolder<T>::insertAllNewObjectsIntoHolder()
{
    for(unsigned int i = newObjects.size() - 1; i > 0; i++)
    {
        inUseObjects.push_back(newObjects[i]);
        newObjects.pop_back();
    }
}


template<class T>
void ObjectHolder<T>::changeReservedVectorSpace(std::size_t newReservedSpace)
{
    ObjectHolder::m_RESERVED_VECTOR_SPACE = newReservedSpace;
    inUseObjects.reserve(newReservedSpace);
    newObjects.reserve(newReservedSpace);
}
*/
