#ifndef CHUNK_H
#define CHUNK_H


#include <array>
#include "ant.h"


class Chunk
{
	private:
		static constexpr unsigned int m_MAX_ANTS_CHUNK = 255;

		void initNearbyChunks(int noOfChunksY, int noOfChunksX);
	public:
		std::array<Ant, m_MAX_ANTS_CHUNK> antsInChunk;
	       	int chunkIndexX, chunkIndexY;
		
		Chunk *pNearbyChunks[3][3];
		
		Chunk(int aChunkIndexX, int aChunkIndexY);
		void chunkInit(std::array<Ant, m_MAX_ANTS_CHUNK> &ants, int totalNoOfChunksY, int totalNoOfChunksX);		
			
};

#endif
