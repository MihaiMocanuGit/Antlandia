#pragma once
#include "Body.h"
#include "WorldKnowledge.h"

class Ant
{
private:
    Body m_body = {};
    WorldKnowledge<Ant> m_knowledge = {};

public:
    Ant() = default;
    explicit Ant(Body body, WorldKnowledge<Ant> knowledge = {});

    [[nodiscard]] const Body& body() const;
    Body& body();

    void insertWorldKnowledge(const WorldKnowledge<Ant> &knowledge);
    [[nodiscard]] const WorldKnowledge<Ant>& knowledge() const;
    WorldKnowledge<Ant>& knowledge();


};
