#ifndef CHUNK_H
#define CHUNK_H


#include <array>
#include "ant.h"


class Chunk
{
	private:
		static constexpr unsigned int m_MAX_ANTS_CHUNK = 255;
        static constexpr unsigned int m_MAX_CHUNKS_X = 8;
        static constexpr unsigned int m_MAX_CHUNKS_Y = 8;

		void initNearbyChunks(int noOfChunksY, int noOfChunksX);
	public:
		std::array<Ant, m_MAX_ANTS_CHUNK> antsInChunk;
	       	int chunkIndexX, chunkIndexY;
		
		Chunk *pNearbyChunks[3][3];
        
        Chunk();       
		Chunk(int aChunkIndexX, int aChunkIndexY);
		
        ///calls initNearbyChunks for every chunk in 2D array. It inits *pNearbyChunks[3][3];
        static void chunksInit(std::array<std::array<Chunk, m_MAX_CHUNKS_X>, m_MAX_CHUNKS_Y> &chunks);

			
};

#endif
