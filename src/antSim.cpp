#include <iostream>
#include "ant.h"
#include "chunk.h"

void initChunks()
{
    
}

int main()
{
	std::cout << "It works!\n";
	


	Ant ant(2, 3, NULL);
	ant.initAnt(99.9f, 69, 2, 0);
	ant.initGenericObject(1, 0.5, 3);

	std::cout << ant.size;
	return 0;
}
