#pragma once
#include "Body.h"
#include "WorldKnowledge.h"
class Pheromone
{
private:
    Body m_body = {};
    WorldKnowledge<Pheromone> m_worldKnowledge = {};
public:
    Pheromone() = default;
    Pheromone(Body body, WorldKnowledge<Pheromone> worldKnowledge);

    Body &body();
    const Body &body() const;

    WorldKnowledge<Pheromone> &knowledge();
    const WorldKnowledge<Pheromone> &knowledge() const;
};

