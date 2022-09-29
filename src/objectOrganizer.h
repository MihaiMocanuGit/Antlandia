#ifndef OBJECT_ORGANIZER_H
#define OBJECT_ORGANIZER_H

#include <array>

#include "chunk.h"
#include "ant.h"
#include "genericObject.h"
#include "objectHolder.h"


///class responsible for creating chunkMap, it controls the structure logic and further calls
template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y, std::size_t MAX_NO_OBJECTS_IN_GROUP>
class ObjectOrganizer
{
private:



        //create chunk map and inits all chunks
        void m_initChunkMap();


public:

        ObjectHolder<Ant, MAX_NO_OBJECTS_IN_GROUP> ants;
        ObjectHolder<GenericObject, MAX_NO_OBJECTS_IN_GROUP> genericObjects;
        
        std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> m_chunkMap;

        ObjectOrganizer();
        ObjectOrganizer(std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> chunkMap);

        //const std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> & getChunkMap() const;
};




#endif