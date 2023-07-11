#pragma once
#include "Body.h"
#include "WorldKnowledge.h"

class GenericObject
{
private:
    Body m_body = {};
    WorldKnowledge m_knowledge = {};

public:
    GenericObject() = default;
    explicit GenericObject(Body body, WorldKnowledge knowledge = {});

    [[nodiscard]] const Body& body() const;
    Body& body();

    void insertWorldKnowledge(const WorldKnowledge &knowledge);
    [[nodiscard]] const WorldKnowledge& knowledge() const;
    WorldKnowledge& knowledge();


};
