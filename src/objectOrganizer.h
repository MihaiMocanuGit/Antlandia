#ifndef OBJECT_ORGANIZER_H
#define OBJECT_ORGANIZER_H

#include <array>

#include "chunk.h"
#include "ant.h"
#include "genericObject.h"
#include "objectHolder.h"




#include <iostream>

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

        sf::Vector2u m_identifyChunkMapIndexForObject(const GenericObject &object)
        {
                sf::Vector2f objectPos = object.pShape->getPosition();
                
                unsigned int xIndex = objectPos.x / Chunk::CHUNK_SIZE.x;
                unsigned int yIndex = objectPos.y / Chunk::CHUNK_SIZE.y;

                return {xIndex, yIndex};
        }

        void m_insertAntIntoWorldChunk(Ant &ant)
        {
                if(ant.m_pHomeChunk == nullptr)
                {
                        sf::Vector2u antPosition = m_identifyChunkMapIndexForObject(ant);

                        unsigned int *pNoOfAnts = &chunkMap[antPosition.y][antPosition.x].noOfAnts;
                        
                        if(chunkMap[antPosition.y][antPosition.x].noOfAnts < Chunk::MAX_ANTS_CHUNK)
                                chunkMap[antPosition.y][antPosition.x].antsInChunk[(*pNoOfAnts)++] = &ant;
                        else std::cout << *pNoOfAnts << '\t';
                        
                        ant.m_pHomeChunk = (void*)(&chunkMap[antPosition.y][antPosition.x]);
                }
        }
public:

        static constexpr std::size_t noOfChunksX = MAP_SIZE_X;
        static constexpr std::size_t noOfChunksY = MAP_SIZE_Y;

        ObjectHolder<Ant> ants{Chunk::MAX_ANTS_CHUNK * noOfChunksX * noOfChunksY};
        //ObjectHolder<GenericObject> genericObjects{Chunk::MAX_ANTS_CHUNK * noOfChunksX * noOfChunksY};

        
        std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> chunkMap;

        ObjectOrganizer()
        {       

               m_initChunkMap();
        }

        //needs to be called only once after every objectHolder.insertAllNewObjectsIntoHolder() call
        void insertAntHolderIntoWorldChunks()
        {
                for( auto& ant : ants.inUseObjects)
                {
                        m_insertAntIntoWorldChunk(ant);
                }
        }

};




#endif