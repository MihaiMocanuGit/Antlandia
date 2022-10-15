#include "ant.h"
#include <iostream>

Ant::Ant() : GenericObject()
{
}


Ant::Ant(sf::CircleShape &aShape, sf::Vector2f &aVelocity, float aHealth, float aEnergy, float aInteractingRadius) 
		: GenericObject(aShape), velocity{aVelocity}, health{aHealth}, energy{aEnergy}, interactingRadius{aInteractingRadius}
{

}

void Ant::init(sf::CircleShape &aShape, sf::Vector2f &aVelocity,  float aHealth, float aEnergy, float aInteractingRadius)
{
	*pShape = aShape;
	velocity = aVelocity;
	health = aHealth;
	energy = aEnergy;
	interactingRadius = aInteractingRadius;
}

