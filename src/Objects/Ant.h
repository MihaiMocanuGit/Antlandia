#pragma once
#include "../ObjectComponents/Body.h"
#include "../ObjectComponents/WorldKnowledge.h"
#include "GenericObject.h"

class Ant
{
public: enum class Type_e; //forward declaration I think
private:
    GenericObject<Ant> m_genericObject;
    Type_e m_type = Type_e::Unknown;
public:
    enum class Type_e {
        Unknown,
        Worker,
        Male,
        Queen,
        Egg,
        COUNT
    };

    Ant() = default;
    explicit Ant(GenericObject<Ant> genericObject, Type_e type = Type_e::Unknown);
    Ant(Body body, WorldKnowledge<Ant> worldKnowledge, Type_e type = Type_e::Unknown);

    Body &body();
    const Body &body() const;

    WorldKnowledge<Ant> &knowledge();
    const WorldKnowledge<Ant> &knowledge() const;

    GenericObject<Ant> &genericObject();
    const GenericObject<Ant> &genericObject() const;
};

