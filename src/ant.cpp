#include "ant.h"
#include <iostream>


Ant::Ant(sf::CircleShape &aShape, sf::Vector2f &aVelocity, float aHealth, float aEnergy, float aInteractingRadius) 
		: GenericObject(aShape, aVelocity), health{aHealth}, energy{aEnergy}, interactingRadius{aInteractingRadius}
{

}

void Ant::init(sf::CircleShape &aShape, sf::Vector2f &aVelocity,  float aHealth, float aEnergy, float aInteractingRadius)
{
	*m_pShape = aShape;
	m_velocity = aVelocity;
	health = aHealth;
	energy = aEnergy;
	interactingRadius = aInteractingRadius;
}

