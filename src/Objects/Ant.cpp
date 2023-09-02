#include "Ant.h"

Ant::Ant(GenericObject<Ant> genericObject, Action_e action) : m_genericObject{std::move(genericObject)}, m_action{action}
{

}

Ant::Ant(Body body, WorldKnowledge<Ant> worldKnowledge, Action_e action)
: Ant(GenericObject<Ant>{std::move(body), std::move(worldKnowledge)}, action)
{

}

Body &Ant::body()
{
    return genericObject().body();
}

const Body &Ant::body() const
{
    return genericObject().body();
}

WorldKnowledge<Ant> &Ant::knowledge()
{
    return genericObject().knowledge();
}

const WorldKnowledge<Ant> &Ant::knowledge() const
{
    return genericObject().knowledge();
}



GenericObject<Ant> &Ant::genericObject()
{
    return m_genericObject;
}

const GenericObject<Ant> &Ant::genericObject() const
{
    return m_genericObject;
}

Ant::Action_e &Ant::action()
{
    return m_action;
}

const Ant::Action_e &Ant::action() const
{
    return m_action;
}

sf::Vector2f &Ant::velocity()
{
    return m_velocity;
}

const sf::Vector2f &Ant::velocity() const
{
    return m_velocity;
}

float &Ant::viewRadius()
{
    return m_viewRadius;
}

const float &Ant::viewRadius() const
{
    return m_viewRadius;
}

float &Ant::interactRadius()
{
    return m_interactRadius;
}

const float &Ant::interactRadius() const
{
    return m_interactRadius;
}

float &Ant::maxVelocity()
{
    return m_maxVelocity;
}

const float &Ant::maxVelocity() const
{
    return m_maxVelocity;
}

Food &Ant::grabbedFood()
{
    return m_grabbedFood;
}

const Food &Ant::grabbedFood() const
{
    return m_grabbedFood;
}
bool &Ant::hasGrabbedFood()
{
    return m_hasGrabbedFood;
}

const bool &Ant::hasGrabbedFood() const
{
    return m_hasGrabbedFood;
}

bool &Ant::hasFoundFood()
{
    return m_hasFoundFood;
}

const bool &Ant::hasFoundFood() const
{
    return m_hasFoundFood;
}

sf::Vector2f &Ant::foundFoodPosition()
{
    return m_foundFoodPosition;
}

const sf::Vector2f &Ant::foundFoodPosition() const
{
    return m_foundFoodPosition;
}

