#ifndef ANT_H
#define ANT_H


#include "genericObject.h"
#include <SFML/Window.hpp>


class Ant : public  GenericObject
{
	private: 
		int m_statusCode; //to be defined later, ex 0 = standby, 1 = searching etc
	public:
		float health;
		float energy;
		
		sf::Vector2f velocity;
		
		
		int getStatusCode();
		void setStatusCode(int statusCode);

		Ant();
		Ant(sf::Vector2f aPosition, sf::Vector2f aVelocity, sf::Color aColor, float aSize, float aHealth, float aEnergy);

};

#endif
