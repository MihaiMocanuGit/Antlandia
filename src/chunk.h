#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include <SFML/Window.hpp>
#include "ant.h"
#include "chunkObjectArray.h"


class Chunk
{
	private:

		void initNearbyChunkMap(sf::Vector2<long unsigned int> noOfChunks);

		struct m_Size
		{
			unsigned int x, y;
		}; 
		
	public:
		static constexpr unsigned int MAX_OBJECTS_PER_TYPE = ChunkObjectArray<Ant>::MAX_OBJECTS_PER_TYPE;

        ChunkObjectArray<Ant> antsArray;
        ChunkObjectArray<Pheromone> pheromonesArray;

		sf::Vector2u chunkIndex;

		static constexpr m_Size CHUNK_SIZE = {50, 50};


		Chunk *pNearbyChunks[3][3] = {{nullptr, nullptr, nullptr},
                                      {nullptr, nullptr, nullptr},
                                      {nullptr, nullptr, nullptr},
                                      };
        
        Chunk();
		explicit Chunk(sf::Vector2u aChunkIndex);
		
        
		///calls initNearbyChunkMap for every chunk in 2D array. It inits *pNearbyChunks[3][3];
		///for initNearbyChunkMap to work, all chunks need to be continuous in memory, eg: std::array
		/*
		 * TODO: Move this into ChunkMap
		 */
        template<std::size_t SIZE_X, std::size_t SIZE_Y>
		static void initAllChunks(std::array<std::array<Chunk, SIZE_X>, SIZE_Y> &chunks)
		{
			for(auto &chunksY : chunks)
        		for(auto &chunkYX : chunksY)
            		chunkYX.initNearbyChunkMap({chunksY.size(), chunks.size()});
		}


};

#endif
