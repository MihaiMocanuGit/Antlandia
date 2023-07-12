#pragma once
#include "ChunkMap.h"

class World
{
private:
    ChunkMap m_map = {};
    SpecializedVector<Ant> m_ants{SpecializedVector<Ant>::SWAP_WORLD};
    SpecializedVector<Pheromone> m_pheromones{SpecializedVector<Pheromone>::SWAP_WORLD};
    SpecializedVector<Food> m_food{SpecializedVector<Food>::SWAP_WORLD};

public:
    World() = default;
    explicit World(sf::Vector2u size);
    World(unsigned sizeX, unsigned sizeY);

    ChunkMap& map();
    SpecializedVector<Ant>& ants();
    SpecializedVector<Pheromone>& pheromones();
    SpecializedVector<Food>& food();

};
