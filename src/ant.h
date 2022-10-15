#ifndef ANT_H
#define ANT_H


#include "genericObject.h"
#include <SFML/Window.hpp>


class Ant : public  GenericObject
{
	private: 
		int m_statusCode; //to be defined later, ex 0 = standby, 1 = searching etc
	public:
		sf::Vector2f velocity;
		
		float health;
		float energy;
		
		int getStatusCode();
		void setStatusCode(int statusCode);

		Ant();
		Ant(sf::CircleShape &aShape, sf::Vector2f &aVelocity,  float aHealth, float aEnergy);

};

#endif
