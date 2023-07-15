#pragma once
#include "Body.h"
#include "WorldKnowledge.h"
class Ant
{
private:
    Body m_body = {};
    WorldKnowledge<Ant> m_worldKnowledge = {};
public:
    Ant() = default;
    Ant(Body body, WorldKnowledge<Ant> worldKnowledge);

    Body &body();
    const Body &body() const;

    WorldKnowledge<Ant> &knowledge();
    const WorldKnowledge<Ant> &knowledge() const;
};

