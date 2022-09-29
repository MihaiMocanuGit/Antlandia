#include "ant.h"
#include <iostream>

Ant::Ant() : GenericObject({-1,-1}, sf::Color::Magenta, 1)
{

}

Ant::Ant(sf::Vector2f aPosition, sf::Vector2f aVelocity, sf::Color aColor, float aSize, float aHealth, float aEnergy) 
		: GenericObject(aPosition, aColor, aSize), health{aHealth}, energy{aEnergy}
{

}



