#ifndef OBJECT_ORGANIZER_H
#define OBJECT_ORGANIZER_H

#include <array>
#include <stdexcept>
#include <iostream>

#include "chunk.h"
#include "ant.h"
#include "genericObject.h"
#include "objectHolder.h"






///class responsible for creating chunkMap, it controls the structure logic and further calls
template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
class ObjectOrganizer
{
private:

        bool m_objectPositionFitsChunkMap(const sf::Vector2f &position)
        {
                
                if(position.x >= 0 and position.y >= 0)
                        if(position.x <= Chunk::CHUNK_SIZE.x * MAP_SIZE_X and position.y <= Chunk::CHUNK_SIZE.y * MAP_SIZE_Y )
                                 return true;
                        else 
                                return false;
                else
                        return false;
        }
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

        sf::Vector2u m_identifyChunkMapIndexFromPosition(const sf::Vector2f &position)
        {       
                if(m_objectPositionFitsChunkMap(position))
                { 

                        unsigned int xIndex = position.x / Chunk::CHUNK_SIZE.x;
                        unsigned int yIndex = position.y / Chunk::CHUNK_SIZE.y;
                        
                        //indexes are from 0 to (MAP_SIZE_ - 1), so if an ant is right on the edge, it would be out of bonds
                        //to correct this, the chunks on the last row/column are made ever so slighty bigger
                        if(xIndex == MAP_SIZE_X) xIndex--;
                        if(yIndex == MAP_SIZE_Y) yIndex--;
                        
                        return {xIndex, yIndex};
                }
                else 
                {
                        throw std::domain_error("object position doesn't fit into chunkMap");
                }
        }

        /*
        void m_findIndexOfAntInChunk(const Ant &ant)
        {
                 sf::Vector2u antMapIndex = m_identifyChunkMapIndexFromPosition(ant.getPosition());

                 for(unsigned int index = 0; index < ants.inUseObjects.size(); index++)
                 {
                        if(&ant == &ants.inUseObjects[index])
                                return index;
                 }
                 return -1;

        }
        //THIS IS SO WRONG
        void m_removeAntFromWorldChunk(Ant &rAnt)
        {

                sf::Vector2u antMapIndex = m_identifyChunkMapIndexFromPosition(rAnt.getPosition());

                //deincrement the counter: noOfAnts used in Chunk 
                //and set pointer of removed ant's home to be NULL
                //I'm using pointer to automatically sync all modifications on noOfAnTS
                unsigned int *pNoOfAnts = &chunkMap[antMapIndex.y][antMapIndex.x].noOfAnts;
        
                //also set the removed ant to null
                (*pNoOfAnts)--;
                chunkMap[antMapIndex.y][antMapIndex.x].antsInChunk[*pNoOfAnts] = nullptr;
                
                //remove home chunk
                rAnt.setPtrHomeChunk(nullptr);

        }

        void m_insertAntIntoWorldChunk(Ant &rAnt)
        {
                //std::cout << rAnt.pShape->getPosition().x << '\n';
     
                sf::Vector2u antMapIndex = m_identifyChunkMapIndexFromPosition(rAnt.getPosition());

                unsigned int *pNoOfAnts = &chunkMap[antMapIndex.y][antMapIndex.x].noOfAnts;
                
                if(chunkMap[antMapIndex.y][antMapIndex.x].noOfAnts < Chunk::MAX_ANTS_CHUNK)
                        chunkMap[antMapIndex.y][antMapIndex.x].antsInChunk[(*pNoOfAnts)++] = &rAnt;
                else 
                        throw std::out_of_range("chunk is already full of ants");
                
                rAnt.setPtrHomeChunk((void*)(&chunkMap[antMapIndex.y][antMapIndex.x]));
   
        }
        */


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

        /*
        //ant must already be in ObjectHolder<Ant>
        void moveAntTo(Ant &rAnt, sf::Vector2f newPosition)
        {
                //sf::Vector2u oldChunkIndex = m_identifyChunkMapIndexFromPositon(rAnt.pShape->getPosition());
                //sf::Vector2u newChunkIndex = m_identifyChunkMapIndexFromPositon(newPosition);
                //if(oldChunkIndex != newChunkIndex)
                m_removeAntFromWorldChunk(rAnt);
                rAnt.setPosition(newPosition);
                m_insertAntIntoWorldChunk(rAnt);
        }
        //if the new position wouldn't fit into the chunkMap, the object wont be moved
        void moveAntBy(Ant &rAnt, sf::Vector2f offset)
        {

                sf::Vector2f newPosition = rAnt.getPosition() + offset;
                if(m_objectPositionFitsChunkMap(newPosition))
                      moveAntTo(rAnt, newPosition);
        }
        */

};




#endif