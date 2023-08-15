#pragma once
#include "GenericObject.h"

class Pheromone
{
private:
    GenericObject<Pheromone> m_genericObject;
public:
    inline const static Body DEFAULT_PHEROMONE_BODY = {sf::Vector2f{-1.0f, -1.0f}, 1.0f, 1.0f,
                                                       sf::Vector3<unsigned char>{0, 255, 0}};
    Pheromone() = default;
    explicit Pheromone(GenericObject<Pheromone> genericObject);
    Pheromone(Body body, WorldKnowledge<Pheromone> worldKnowledge);

    Body &body();
    const Body &body() const;

    WorldKnowledge<Pheromone> &knowledge();
    const WorldKnowledge<Pheromone> &knowledge() const;

    GenericObject<Pheromone> &genericObject();
    const GenericObject<Pheromone> &genericObject() const;
};

