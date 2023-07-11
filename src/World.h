#pragma once
#include "ChunkMap.h"

class World
{
private:
    ChunkMap m_map;
    SpecializedVector<GenericObject> m_ants;
    SpecializedVector<GenericObject> m_pheromones;
    SpecializedVector<GenericObject> m_food;
public:
    World() = default;

};
