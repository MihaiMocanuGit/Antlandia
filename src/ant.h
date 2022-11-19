#ifndef ANT_H
#define ANT_H

#include <SFML/Window.hpp>
#include "genericObject.h"
#include "pheromone.h"



class Ant : public  GenericObject
{
	private: 
		int m_statusCode; //to be defined later, ex 0 = standby, 1 = searching etc
	public:

		
		float health;
		float energy;
		float interactingRadius;

		int getStatusCode();
		void setStatusCode(int statusCode);

		Ant();
		Ant(sf::CircleShape &aShape, sf::Vector2f &aVelocity,  float aHealth, float aEnergy, float aInteractingRadius);

        /*
         * TODO: THINK HOW TO CHANGE THE STRUCTURE LEVELS TO IMPLEMENT THIS
         *          see TODO.txt for more info
         */
        void dischargePheromone(int pheromoneType);

		void init(sf::CircleShape &aShape, sf::Vector2f &aVelocity,  float aHealth, float aEnergy, float aInteractingRadius);
};

#endif
