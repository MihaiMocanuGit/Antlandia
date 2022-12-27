#include "chunk.h"

Chunk::Chunk() = default;


Chunk::Chunk(sf::Vector2u aChunkIndex) : chunkIndex{aChunkIndex}
{
}

void Chunk::initNearbyChunkMap(sf::Vector2<long unsigned int> noOfChunks)
{

	for (int y = -1; y <= 1; y++)
		for(int x = -1; x <= 1; x++)
		{
			if(chunkIndex.x + x >= 0 and chunkIndex.x + x < noOfChunks.x and
			   chunkIndex.y + y >= 0 and chunkIndex.y + y < noOfChunks.y)
				pNearbyChunks[1 + y][1 + x] = this + x + noOfChunks.x * y;
            else
                pNearbyChunks[1 + y][1 + x] = nullptr;

		}
}
