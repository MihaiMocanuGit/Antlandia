#pragma once
#include "GenericObject.h"

class Pheromone
{
private:
    GenericObject<Pheromone> m_genericObject;
public:
    Pheromone() = default;
    explicit Pheromone(GenericObject<Pheromone> genericObject);
    Pheromone(Body body, WorldKnowledge<Pheromone> worldKnowledge);

    Body &body();
    const Body &body() const;

    WorldKnowledge<Pheromone> &knowledge();
    const WorldKnowledge<Pheromone> &knowledge() const;

    GenericObject<Pheromone> &genericObject();
    const GenericObject<Pheromone> &genericObject() const;
};

