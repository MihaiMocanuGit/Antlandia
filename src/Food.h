#pragma once
#include "Body.h"
#include "WorldKnowledge.h"
class Food
{
private:
    Body m_body = {};
    WorldKnowledge m_worldKnowledge = {};
public:
    Food() = default;
    Food(Body body, WorldKnowledge worldKnowledge);

    Body &body();
    const Body &body() const;

    WorldKnowledge &knowledge();
    const WorldKnowledge &knowledge() const;
};

