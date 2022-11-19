//
// Created by mihai on 11/19/22.
//

#include "pheromone.h"

Pheromone::Pheromone()
{

}


Pheromone::Pheromone(sf::CircleShape &aShape, float aPower, float aPowerReducingFactor)
{
    m_pShape = &aShape;
    powerReducingFactor = aPowerReducingFactor;
    power = aPower;

    /*
     * TODO: rethink if this should be implemented as an error or a neutral value reallocation
    */
    if(powerReducingFactor < 1)
        powerReducingFactor = Pheromone::DEFAULT_POWER_REDUCING_FACTOR;

}

void Pheromone::update()
{
    power = power/powerReducingFactor;
}

bool Pheromone::isThisPheromoneDepleted()
{
    return power < Pheromone::epsilon_zero_power;
}

