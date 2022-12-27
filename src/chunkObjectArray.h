#ifndef CHUNK_OBJECT_ARRAY_H
#define CHUNK_OBJECT_ARRAY_H

#include "genericObject.h"

/*
 * TODO: Change from T to T*
 */
template <class T>
class ChunkObjectArray
{
public:
    static_assert(std::is_base_of<GenericObject, T>::value, "T must inherit from GenericObject");
    static constexpr unsigned int MAX_OBJECTS_PER_TYPE = 1024;
    unsigned int noOfObjects = 0;

    std::array<T*, ChunkObjectArray::MAX_OBJECTS_PER_TYPE> objectsInChunk;

    void optimizeArray();
};

#endif //CHUNK_OBJECT_ARRAY_H
