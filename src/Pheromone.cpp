#include "Pheromone.h"

Pheromone::Pheromone(Body body, WorldKnowledge<Pheromone> worldKnowledge) : m_body{std::move(body)}, m_worldKnowledge{std::move(worldKnowledge)}
{

}

Body &Pheromone::body()
{
    return m_body;
}

const Body &Pheromone::body() const
{
    return m_body;
}

WorldKnowledge<Pheromone> &Pheromone::knowledge()
{
    return m_worldKnowledge;
}

const WorldKnowledge<Pheromone> &Pheromone::knowledge() const
{
    return m_worldKnowledge;
}
