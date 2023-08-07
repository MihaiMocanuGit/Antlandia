#include "Ant.h"

Ant::Ant(Body body, WorldKnowledge<Ant> worldKnowledge) : Ant(GenericObject<Ant>{std::move(body), std::move(worldKnowledge)})
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

Ant::Ant(GenericObject<Ant> genericObject) : m_genericObject{std::move(genericObject)}
{

}

GenericObject<Ant> &Ant::genericObject()
{
    return m_genericObject;
}

const GenericObject<Ant> &Ant::genericObject() const
{
    return m_genericObject;
}
