#include "Pheromone.h"
#include <algorithm>

Pheromone::Pheromone(GenericObject<Pheromone> genericObject, Type_e type, float halfLife)
        : m_genericObject{std::move(genericObject)}, m_type{std::move(type)}, m_massHalfLife{halfLife},
        m_initialMass{m_genericObject.body().getMass()}, m_initialAlpha{m_genericObject.body().getColor().a}
{
}

Pheromone::Pheromone(Body body, WorldKnowledge<Pheromone> worldKnowledge, Type_e type, float halfLife)
: Pheromone(GenericObject<Pheromone>{std::move(body),std::move(worldKnowledge)}, std::move(type), halfLife)
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

    const float minimumValue = 100;
    const float newAlpha = newMass / m_initialMass * (m_initialAlpha+minimumValue) + minimumValue;

    sf::Color newColor = m_genericObject.body().getColor();
    newColor.a = std::clamp(newAlpha, 0.0f, 255.0f);

    m_genericObject.body().setColor(newColor);

    return newMass > almostZero;
}
