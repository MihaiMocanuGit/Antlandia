#include "World.h"

World::World(sf::Vector2u size) : m_map(size)
{

}

World::World(unsigned int sizeX, unsigned int sizeY) : World(sf::Vector2u {sizeX, sizeY})
{

}

SpecializedVector<GenericObject> &World::ants()
{
    return m_ants;
}

SpecializedVector<GenericObject> &World::food()
{
    return m_food;
}

SpecializedVector<GenericObject> &World::pheromones()
{
    return m_pheromones;
}

ChunkMap &World::map()
{
    return m_map;
}
