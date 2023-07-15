#pragma once
#include "Body.h"
#include "WorldKnowledge.h"
class Pheromone
{
private:
    Body m_body = {};
    WorldKnowledge m_worldKnowledge = {};
public:
    Pheromone() = default;
    Pheromone(Body body, WorldKnowledge worldKnowledge);

    Body &body();
    const Body &body() const;

    WorldKnowledge &knowledge();
    const WorldKnowledge &knowledge() const;
};

