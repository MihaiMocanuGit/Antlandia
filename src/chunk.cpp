#include "chunk.h"

Chunk::Chunk() 
{
}

Chunk::Chunk(int aChunkIndexX, int aChunkIndexY) : chunkIndexX(aChunkIndexX), chunkIndexY(aChunkIndexY)
{
}

void Chunk::initNearbyChunks(int noOfChunksY, int noOfChunksX)
{

	for (int y = -1; y <= 1; y++)
		for(int x = -1; x <= 1; x++)
		{
			if(chunkIndexX + x >= 0 and chunkIndexX + x < noOfChunksX and
			   chunkIndexY + y >= 0 and chunkIndexY + y < noOfChunksY)
				pNearbyChunks[1 + y][1 + x] = this + x + noOfChunksX * y;
            else
                pNearbyChunks[1 + y][1 + x] = nullptr;

		}
}

/*
template<std::size_t SIZE_X, std::size_t SIZE_Y>
void Chunk::chunksInit(std::array<std::array<Chunk, SIZE_X>, SIZE_Y> &chunks)
{
    for(auto &chunksY : chunks)
        for(auto &chunkYX : chunksY)
            chunkYX.initNearbyChunks(chunksY.size(), chunks.size());
}
*/
