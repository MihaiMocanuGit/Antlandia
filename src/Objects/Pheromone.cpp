#include "Pheromone.h"


Pheromone::Pheromone(Body body, WorldKnowledge<Pheromone> worldKnowledge)
        : Pheromone(GenericObject<Pheromone>{std::move(body),std::move(worldKnowledge)})
{

}

Body &Pheromone::body()
{
    return m_genericObject.body();
}

const Body &Pheromone::body() const
{
    return m_genericObject.body();
}

WorldKnowledge<Pheromone> &Pheromone::knowledge()
{
    return m_genericObject.knowledge();
}

const WorldKnowledge<Pheromone> &Pheromone::knowledge() const
{
    return m_genericObject.knowledge();
}

Pheromone::Pheromone(GenericObject<Pheromone> genericObject) : m_genericObject{std::move(genericObject)}
{

}

GenericObject<Pheromone> &Pheromone::genericObject()
{
    return m_genericObject;
}

const GenericObject<Pheromone> &Pheromone::genericObject() const
{
    return m_genericObject;
}

bool Pheromone::decreasePotency(unsigned int noFramesPassed, float almostZero)
{
    //In massHalfLife frames    ----> mass / 2
    //In noFramesPassed         ----> x mass
    // => x = (mass / 2 * noFramesPassed) / massHalfLife

    const float oldMass = m_genericObject.body().getMass();
    const float newMass = oldMass - ((oldMass / 2.0f) * (float)noFramesPassed) / m_massHalfLife;
    m_genericObject.body().setMass(newMass);

    return newMass > almostZero;
}
