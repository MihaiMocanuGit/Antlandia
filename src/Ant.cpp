#include "Ant.h"

Ant::Ant(Body body, WorldKnowledge worldKnowledge) : m_body{std::move(body)}, m_worldKnowledge{std::move(worldKnowledge)}
{

}

Body &Ant::body()
{
    return m_body;
}

const Body &Ant::body() const
{
    return m_body;
}

WorldKnowledge &Ant::knowledge()
{
    return m_worldKnowledge;
}

const WorldKnowledge &Ant::knowledge() const
{
    return m_worldKnowledge;
}
