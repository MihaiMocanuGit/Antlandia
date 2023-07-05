#pragma once
#include "Body.h"
#include "WorldKnowledge.h"

class Ant
{
private:
    Body m_body = {};
    WorldKnowledge m_world = {};
public:
    Ant() = default;
    explicit Ant(Body body, WorldKnowledge word = {});

    [[nodiscard]] const Body& body() const;
    Body& body();

    void insertWorldKnowledge(const WorldKnowledge &world);
    [[nodiscard]] const WorldKnowledge& world() const;
    WorldKnowledge& world();


};
