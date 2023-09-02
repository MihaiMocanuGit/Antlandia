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

Ant &World::prepareAnt(sf::Vector2f position, float size, float mass, const sf::Color &color)
{
    Body body(position, size, mass, color);
    return prepareAnt(body);
}
Ant &World::prepareAnt(const Body &antBody)
{
    return m_spawner.prepareObject(antBody, m_ants, m_map.primitiveChunkMaps().antMap);
}
Ant &World::prepareAnt(const Ant &ant)
{
    return m_spawner.prepareObject(ant, m_ants, m_map.primitiveChunkMaps().antMap);
}



Pheromone &World::preparePheromone(sf::Vector2f position, float size, float mass, const sf::Color &color)
{
    Body body(position, size, mass, color);
    return preparePheromone(body);
}

Pheromone &World::preparePheromone(const Body &pheromoneBody)
{
    return m_spawner.prepareObject(pheromoneBody, m_pheromones, m_map.primitiveChunkMaps().pheromoneMap);;
}
Pheromone &World::preparePheromone(const Pheromone &pheromone)
{
    return m_spawner.prepareObject(pheromone, m_pheromones, m_map.primitiveChunkMaps().pheromoneMap);
}



Food &World::prepareFood(sf::Vector2f position, float size, float mass, const sf::Color &color)
{
    Body body(position, size, mass, color);
    return prepareFood(body);
}
Food &World::prepareFood(const Body &foodBody)
{
    return m_spawner.prepareObject(foodBody, m_food, m_map.primitiveChunkMaps().foodMap);
}
Food &World::prepareFood(const Food &food)
{
    return m_spawner.prepareObject(food, m_food, m_map.primitiveChunkMaps().foodMap);
}



Pheromone &World::makeAntSpawnPheromone(const Ant &ant, const Pheromone &pheromone)
{
    Pheromone pheromoneMovedIntoAnt = pheromone;
    pheromoneMovedIntoAnt.body().setPosition(ant.body().getPosition());
    return preparePheromone(pheromoneMovedIntoAnt);
}

Pheromone &World::makeAntSpawnPheromone(const Ant &ant, const Body &pheromoneBody)
{
    Body pheromoneBodyMovedIntoAnt = pheromoneBody;
    pheromoneBodyMovedIntoAnt.setPosition(ant.body().getPosition());
    return preparePheromone(pheromoneBodyMovedIntoAnt);
}

