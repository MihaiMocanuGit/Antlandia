#pragma once
#include "../ObjectComponents/Body.h"
#include "../ObjectComponents/WorldKnowledge.h"
#include "GenericObject.h"

class Ant
{
private:
    GenericObject<Ant> m_genericObject;
public:
    Ant() = default;
    explicit Ant(GenericObject<Ant> genericObject);
    Ant(Body body, WorldKnowledge<Ant> worldKnowledge);

    Body &body();
    const Body &body() const;

    WorldKnowledge<Ant> &knowledge();
    const WorldKnowledge<Ant> &knowledge() const;

    GenericObject<Ant> &genericObject();
    const GenericObject<Ant> &genericObject() const;
};

