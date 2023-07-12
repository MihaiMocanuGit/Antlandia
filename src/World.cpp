#include "World.h"

World::World(sf::Vector2u size) : m_map(size)
{

}

World::World(unsigned int sizeX, unsigned int sizeY) : World(sf::Vector2u {sizeX, sizeY})
{

}

SpecializedVector<Ant> &World::ants()
{
    return m_ants;
}

SpecializedVector<Food> &World::food()
{
    return m_food;
}

SpecializedVector<Pheromone> &World::pheromones()
{
    return m_pheromones;
}

ChunkMap &World::map()
{
    return m_map;
}

sf::Vector2u World::size() const
{
    return m_map.size();
}

