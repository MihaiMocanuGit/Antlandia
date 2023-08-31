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
