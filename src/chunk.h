#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include <SFML/Window.hpp>
#include "ant.h"


class Chunk
{
	private:
		static constexpr unsigned int m_MAX_ANTS_CHUNK = 255;

		void initNearbyChunkMap(sf::Vector2i noOfChunks);
	public:
		std::array<Ant, m_MAX_ANTS_CHUNK> antsInChunk;
	    
		sf::Vector2i chunkIndex;

		//needs to be constexpr/const/private with get
        sf::Vector2i chunkSize = {128, 128};

		Chunk *pNearbyChunks[3][3];
        
        Chunk();       
		Chunk(sf::Vector2i aChunkIndex);
		
        
		///calls initNearbyChunkMap for every chunk in 2D array. It inits *pNearbyChunks[3][3];
        template<std::size_t SIZE_X, std::size_t SIZE_Y>
		static void initAllChunks(std::array<std::array<Chunk, SIZE_X>, SIZE_Y> &chunks)
		{
			for(auto &chunksY : chunks)
        		for(auto &chunkYX : chunksY)
            		chunkYX.initNearbyChunkMap(chunksY.size(), chunks.size());
		}

			
};

#endif
