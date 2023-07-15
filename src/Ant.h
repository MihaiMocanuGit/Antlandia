#pragma once
#include "Body.h"
#include "WorldKnowledge.h"
class Ant
{
private:
    Body m_body = {};
    WorldKnowledge m_worldKnowledge = {};
public:
    Ant() = default;
    Ant(Body body, WorldKnowledge worldKnowledge);

    Body &body();
    const Body &body() const;

    WorldKnowledge &knowledge();
    const WorldKnowledge &knowledge() const;
};

