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
        void m_initChunkMap()
        {
                for(unsigned int y = 0; y < chunkMap.size(); y++)
                {
                    for(unsigned int x = 0; x < chunkMap[y].size(); x++)
                    {
                        chunkMap[y][x] = Chunk({x,y});
                    }
                }            
                Chunk::initAllChunks(chunkMap);    
        }



public:

        static constexpr std::size_t noOfChunksX = MAP_SIZE_X;
        static constexpr std::size_t noOfChunksY = MAP_SIZE_Y;

        ObjectHolder<Ant> ants{Chunk::MAX_ANTS_CHUNK * noOfChunksX * noOfChunksY};
        ObjectHolder<GenericObject> genericObjects{Chunk::MAX_ANTS_CHUNK * noOfChunksX * noOfChunksY};


        std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> chunkMap;

        ObjectOrganizer()
        {       

               m_initChunkMap();
        }

};




#endif