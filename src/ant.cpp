#include "ant.h"
#include <iostream>

Ant::Ant() : GenericObject()
{
}


Ant::Ant(sf::CircleShape &aShape, sf::Vector2f &aVelocity, float aHealth, float aEnergy) 
		: GenericObject(aShape), velocity{aVelocity}, health{aHealth}, energy{aEnergy}
{

}




