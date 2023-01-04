//
// Created by mihai on 11/19/22.
//

#include "pheromone.h"

Pheromone::Pheromone(sf::CircleShape &aShape, int aType, float aPower, float aPowerReducingFactor)
    : GenericObject(aShape, {0, 0}), type(aType), power(aPower), powerReducingFactor(aPowerReducingFactor < 1 ? 1 : aPowerReducingFactor )
{

}

void Pheromone::update()
{
    power = power/powerReducingFactor;
    isDead = isThisDepleted();
}

bool Pheromone::isThisDepleted()
{
    return power < Pheromone::epsilon_zero_power;
}

