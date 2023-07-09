#pragma once
#include "Body.h"
#include "WorldKnowledge.h"

class GenericObject
{
private:
    Body m_body = {};
    WorldKnowledge<GenericObject> m_knowledge = {};

public:
    GenericObject() = default;
    explicit GenericObject(Body body, WorldKnowledge<GenericObject> knowledge = {});

    [[nodiscard]] const Body& body() const;
    Body& body();

    void insertWorldKnowledge(const WorldKnowledge<GenericObject> &knowledge);
    [[nodiscard]] const WorldKnowledge<GenericObject>& knowledge() const;
    WorldKnowledge<GenericObject>& knowledge();


};
