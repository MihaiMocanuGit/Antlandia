#ifndef OBJECT_ORGANIZER_H
#define OBJECT_ORGANIZER_H

#include <array>

#include "chunk.h"
#include "genericObject.h"
#include "objectOrganizer.h"

///create chunkMap, it controls the structure logic further calls
template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y, std::size_t MAX_NO_OBJECTS_IN_GROUP>
class ObjectOrganizer
{
private:

        std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> m_chunkMap;

        //create chunk map and inits all chunks
        void m_initChunkMap();


public:

        ObjectOrganizer()

        ObjectHolder<Ant, MAX_NO_OBJECTS_IN_GROUP> ants;
        ObjectHolder<GenericObject, MAX_NO_OBJECTS_IN_GROUP> GenericObject;

        const std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> & getChunkMap() const;
};




#endif