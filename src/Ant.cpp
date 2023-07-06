#include <utility>
#include "Ant.h"

Ant::Ant(Body body, WorldKnowledge<Ant> knowledge) : m_body{std::move(body)}, m_knowledge{std::move(knowledge)}
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

void Ant::insertWorldKnowledge(const WorldKnowledge<Ant> &knowledge)
{
    m_knowledge = knowledge;
}

const WorldKnowledge<Ant> &Ant::knowledge() const
{
    return m_knowledge;
}

WorldKnowledge<Ant> &Ant::knowledge()
{
    return m_knowledge;
}
