#include "genericObject.h"
#include <iostream>



GenericObject::GenericObject(float aX, float aY, void *aPHomeChunk) : pHomeChunk(aPHomeChunk), coordX(aX), coordY(aY)
{

}


void GenericObject::initGenericObject(int aColorCode, float aColorIntensity, float aSize)
{
	colorCode = aColorCode;
	colorIntensity = aColorIntensity;
	size = aSize;
}



