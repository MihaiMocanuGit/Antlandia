#pragma once
#include "ChunkMap.h"

class World
{
private:
    ChunkMap m_map = {};
    SpecializedVector<GenericObject> m_ants{SpecializedVector<GenericObject>::SWAP_WORLD};
    SpecializedVector<GenericObject> m_pheromones{SpecializedVector<GenericObject>::SWAP_WORLD};
    SpecializedVector<GenericObject> m_food{SpecializedVector<GenericObject>::SWAP_WORLD};

public:
    World() = default;
    explicit World(sf::Vector2u size);
    World(unsigned sizeX, unsigned sizeY);

    ChunkMap& map();
    SpecializedVector<GenericObject>& ants();
    SpecializedVector<GenericObject>& pheromones();
    SpecializedVector<GenericObject>& food();

};
