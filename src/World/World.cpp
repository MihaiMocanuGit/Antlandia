#include "World.h"

World::World() : m_spawner(this, m_map), m_mover(m_map)
{

}
World::World(sf::Vector2u size) : m_map(size,SpecializedVectorAllTypes(m_ants, m_food, m_pheromones)),\
                                    m_spawner(this, m_map), m_mover(m_map)
{

}

World::World(unsigned int sizeX, unsigned int sizeY) : World(sf::Vector2u {sizeX, sizeY})
{

}

SpecializedVector<Ant> &World::ants()
{
    return m_ants;
}
const SpecializedVector<Ant> &World::ants() const
{
    return m_ants;
}



SpecializedVector<Food> &World::food()
{
    return m_food;
}

const SpecializedVector<Food> &World::food() const
{
    return m_food;
}


SpecializedVector<Pheromone> &World::pheromones()
{
    return m_pheromones;
}
const SpecializedVector<Pheromone> &World::pheromones() const
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

Ant &World::prepareAnt(sf::Vector2f position, float size, float mass, const sf::Vector3<unsigned char> &color)
{
    Body body(position, size, mass, color);
    return m_spawner.prepareObject(body, m_ants, m_map.primitiveChunkMaps().antMap);
}

Pheromone &World::preparePheromone(sf::Vector2f position, float size, float mass, const sf::Vector3<unsigned char> &color)
{
    Body body(position, size, mass, color);
    return m_spawner.prepareObject(body, m_pheromones, m_map.primitiveChunkMaps().pheromoneMap);
}

Food &World::prepareFood(sf::Vector2f position, float size, float mass, const sf::Vector3<unsigned char> &color)
{
    Body body(position, size, mass, color);
    return m_spawner.prepareObject(body, m_food, m_map.primitiveChunkMaps().foodMap);
}



