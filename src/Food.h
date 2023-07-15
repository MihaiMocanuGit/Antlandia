#pragma once
#include "Body.h"
#include "WorldKnowledge.h"
class Food
{
private:
    Body m_body = {};
    WorldKnowledge<Food> m_worldKnowledge = {};
public:
    Food() = default;
    Food(Body body, WorldKnowledge<Food> worldKnowledge);

    Body &body();
    const Body &body() const;

    WorldKnowledge<Food> &knowledge();
    const WorldKnowledge<Food> &knowledge() const;
};

