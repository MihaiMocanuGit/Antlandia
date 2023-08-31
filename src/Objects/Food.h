#pragma once
#include "GenericObject.h"

class Food
{
private:
    GenericObject<Food> m_genericObject;

    //A food particle is locked if an ant is going to grab it, meaning that other ants cannot
    //take this food particle; Furthermore, such food cannot decay anymore
    bool m_isLocked = false;
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

    bool &isLocked();
    bool &isLocked() const;

};

