#include "Ant.h"

Ant::Ant(GenericObject<Ant> genericObject, Type_e type) : m_genericObject{std::move(genericObject)}, m_type{type}
{

}

Ant::Ant(Body body, WorldKnowledge<Ant> worldKnowledge, Type_e type)
: Ant(GenericObject<Ant>{std::move(body), std::move(worldKnowledge)}, type)
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
