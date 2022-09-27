#ifndef CHUNK_H
#define CHUNK_H


#include <array>
#include "ant.h"


class Chunk
{
	private:
		static constexpr unsigned int m_MAX_ANTS_CHUNK;

		void initNearbyChunks(int noOfChunksY, int noOfChunksX);
	public:
		std::array<Ant, m_MAX_ANTS_CHUNK> antsInChunk;
	    int chunkIndexX, chunkIndexY;
		
        static constexpr int CHUNK_SIZE_X = 128;
		static constexpr int CHUNK_SIZE_Y = 128;

		Chunk *pNearbyChunks[3][3];
        
        Chunk();       
		Chunk(int aChunkIndexX, int aChunkIndexY);
		
        
		///calls initNearbyChunks for every chunk in 2D array. It inits *pNearbyChunks[3][3];
        template<std::size_t SIZE_X, std::size_t SIZE_Y>
		static void chunksInit(std::array<std::array<Chunk, SIZE_X>, SIZE_Y> &chunks)
		{
			for(auto &chunksY : chunks)
        		for(auto &chunkYX : chunksY)
            		chunkYX.initNearbyChunks(chunksY.size(), chunks.size());
		}

			
};

#endif
