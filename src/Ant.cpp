#include <utility>
#include "Ant.h"

Ant::Ant(Body body, WorldKnowledge word) : m_body{std::move(body)}, m_world{std::move(word)}
{

}

const Body &Ant::body() const
{
    return m_body;
}

Body &Ant::body()
{
    return m_body;
}

void Ant::insertWorldKnowledge(const WorldKnowledge &world)
{
    m_world = world;
}

const WorldKnowledge &Ant::world() const
{
    return m_world;
}

WorldKnowledge &Ant::world()
{
    return m_world;
}
