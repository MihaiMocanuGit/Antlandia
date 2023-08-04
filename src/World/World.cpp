#include "World.h"


World::World(sf::Vector2u size) : m_map(size,SpecializedVectorAllTypes(m_ants, m_food, m_pheromones))
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

Ant &World::addAnt(sf::Vector2f position, float size, float mass, const sf::Vector3<unsigned char> &color)
{
    Body body(position, size, mass, color);
    Ant ant = m_createObject<Ant>(body, m_ants, m_map.primitiveChunkMaps().antMap);

    m_ants.toBeAdded(ant);

    Ant &refReturn = m_ants.atAddBuffer(m_ants.sizeAddBuffer() - 1);
    //m_map.at(refReturn.knowledge().homeChunkIndex()).ref_antChunk.objects.toBeAdded(&refReturn);
    return refReturn;
}

Pheromone &World::addPheromone(sf::Vector2f position, float size, float mass, const sf::Vector3<unsigned char> &color)
{
    Body body(position, size, mass, color);
    Pheromone pheromone = m_createObject<Pheromone>(body, m_pheromones, m_map.primitiveChunkMaps().pheromoneMap);


    m_pheromones.toBeAdded(pheromone);

    Pheromone &refReturn = m_pheromones.atAddBuffer(m_pheromones.sizeAddBuffer() - 1);
    //m_map.at(refReturn.knowledge().homeChunkIndex()).ref_pheromoneChunk.objects.toBeAdded(&refReturn);
    return refReturn;
}

Food &World::addFood(sf::Vector2f position, float size, float mass, const sf::Vector3<unsigned char> &color)
{
    Body body(position, size, mass, color);
    Food food = m_createObject<Food>(body, m_food, m_map.primitiveChunkMaps().foodMap);

    m_food.toBeAdded(food);

    Food &refReturn = m_food.atAddBuffer(m_food.sizeAddBuffer() - 1);
    //m_map.at(refReturn.knowledge().homeChunkIndex()).ref_foodChunk.objects.toBeAdded(&refReturn);
    return refReturn;
}


