#include "chunk.h"

//int Chunk::m_MAX_ANTS_CHUNK = 255;


Chunk::Chunk(int aChunkIndexX, int aChunkIndexY) : chunkIndexX{aChunkIndexX}, chunkIndexY{aChunkIndexY}
{
}

void Chunk::initNearbyChunks(int noOfChunksY, int noOfChunksX)
{
	for (int y = -1; y <= 1; y++)
		for(int x = -1; x <= 1; x++)
		{
			if(chunkIndexX + x >= 0 and chunkIndexX + x < noOfChunksX and
			   chunkIndexY + y >= 0 and chunkIndexY + y < noOfChunksY)
				pNearbyChunks[y][x] = this + x + 3 * y;

		}
}
