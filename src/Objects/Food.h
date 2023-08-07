#pragma once
#include "GenericObject.h"

class Food
{
private:
    GenericObject<Food> m_genericObject;
public:
    Food() = default;
    explicit Food(GenericObject<Food> genericObject);
    Food(Body body, WorldKnowledge<Food> worldKnowledge);

    Body &body();
    const Body &body() const;

    WorldKnowledge<Food> &knowledge();
    const WorldKnowledge<Food> &knowledge() const;

    GenericObject<Food> &genericObject();
    const GenericObject<Food> &genericObject() const;
};

