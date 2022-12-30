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

		Ant() = default;
		Ant(sf::CircleShape &aShape, sf::Vector2f &aVelocity,  float aHealth, float aEnergy, float aInteractingRadius);

        /*
         * TODO: THINK HOW TO CHANGE THE STRUCTURE LEVELS TO IMPLEMENT THIS
         *          see TODO.txt for more info
         * TODO: Should this be a template function in genericObject?
         */
        ///
        /// \tparam MAP_SIZE_X
        /// \tparam MAP_SIZE_Y
        /// \param rWorld
        /// \param rPheromone: The pheromone to be discharged, it will inherit the ant's position at that time
        /// \return The index of the pheromone in <Pheromone> holder (from pheromoneController)
        template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
        unsigned int dischargePheromone(World<MAP_SIZE_X, MAP_SIZE_Y> &rWorld, Pheromone &rPheromone)
        {
            return rWorld.antController.dischargeObjectFromParentAtIndex(m_indexInHolder,
                                                                         rPheromone, rWorld.pheromoneController);
        }

		void init(sf::CircleShape &aShape, sf::Vector2f &aVelocity,
                  float aHealth, float aEnergy, float aInteractingRadius);
};

#endif
