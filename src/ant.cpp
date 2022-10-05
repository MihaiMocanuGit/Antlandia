#include "ant.h"
#include <iostream>

Ant::Ant() : GenericObject()
{
	sf::CircleShape dummyShape(5);
	m_initPtrShape(dummyShape);
}


Ant::Ant(sf::CircleShape &aShape, sf::Vector2f &aVelocity, float aHealth, float aEnergy) 
		: GenericObject(aShape), velocity{aVelocity}, health{aHealth}, energy{aEnergy}
{

}




