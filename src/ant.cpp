#include "ant.h"
#include <iostream>

Ant::Ant() : GenericObject()
{
}


Ant::Ant(DEBBUG_TYPE &aShape, sf::Vector2f &aVelocity, float aHealth, float aEnergy) 
		: GenericObject(aShape), velocity{aVelocity}, health{aHealth}, energy{aEnergy}
{

}




