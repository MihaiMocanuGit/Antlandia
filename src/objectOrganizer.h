#ifndef OBJECT_ORGANIZER_H
#define OBJECT_ORGANIZER_H

#include <array>

#include "chunk.h"
#include "ant.h"
#include "genericObject.h"
#include "objectHolder.h"


///class responsible for creating chunkMap, it controls the structure logic and further calls
template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
class ObjectOrganizer
{
private:

        //create chunk map and inits all chunks
        void m_initChunkMap();

        //void m_initNoOfChunks();
public:

        static constexpr std::size_t noOfChunksX = MAP_SIZE_X;
        static constexpr std::size_t noOfChunksY = MAP_SIZE_Y;

        ObjectHolder<Ant> ants{Chunk::MAX_ANTS_CHUNK * noOfChunksX * noOfChunksY};
        ObjectHolder<GenericObject> genericObjects{Chunk::MAX_ANTS_CHUNK * noOfChunksX * noOfChunksY / 3};


        std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> chunkMap;

        ObjectOrganizer();
        ObjectOrganizer(std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> chunkMap);

};




#endif