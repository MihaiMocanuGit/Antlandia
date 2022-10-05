#include "ant.h"
#include <iostream>

Ant::Ant() : GenericObject(sf::CircleShape(5))
{
	pShape->setFillColor(sf::Color::Magenta);
	pShape->setPosition(-1, -1);
}


Ant::Ant(sf::CircleShape aShape, sf::Vector2f aVelocity, float aHealth, float aEnergy) 
		: GenericObject(aShape), velocity{aVelocity}, health{aHealth}, energy{aEnergy}
{

}




