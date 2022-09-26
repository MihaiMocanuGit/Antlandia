#include <iostream>
#include "ant.h"
#include "chunk.h"

void initChunks(std::array<std::array<Chunk, 8>, 8> &chunks) 
{
    for(int y = 0; y < chunks.size(); y++)
    {
        for(int x = 0; x < chunks[y].size(); x++)
        {
            chunks[y][x] = Chunk(x,y);
        }
    }
    
    Chunk::chunksInit(chunks);    
}

int main()
{
	std::cout << "It works!\n";
	


	Ant ant(2, 3, NULL);
	ant.initAnt(99.9f, 69, 2, 0);
	ant.initGenericObject(1, 0.5, 3);

	std::cout << ant.size << '\n';
    
    std::array<std::array<Chunk, 8>, 8> chunks;
    initChunks(chunks);  
    
    for( auto & chunksY : chunks)
    {
        for( auto & chunkYX : chunksY)
        {
            std::cout <<  &chunkYX << '\t';
        }
        std::cout << '\n';
    }

    std::cout << "\n\n\n";

   for( auto & chunksY : chunks)
   {
       for( auto & chunkYX : chunksY)
       {
           std::cout <<  chunkYX.pNearbyChunks[0][0] << '\t';
       }
       std::cout << '\n';
   }

    return 0;
}
