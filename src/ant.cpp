#include "ant.h"
#include <iostream>

Ant::Ant() : GenericObject( -1, -1, nullptr)
{

}

Ant::Ant(float aX, float aY, void *aPHomeChunk) : GenericObject(aX, aY, aPHomeChunk)
{

}

void Ant::initAnt(float aHealth, float aEnergy, float aVelDirX, float aVelDirY)
{
	health = aHealth;
	energy = aEnergy;
	velDirX = aVelDirX;
	velDirY = aVelDirY;
}

