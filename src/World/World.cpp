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

Ant &World::prepareAnt(sf::Vector2f position, float size, float mass, const sf::Vector3<unsigned char> &color)
{
    Body body(position, size, mass, color);
    Ant ant = m_createObject<Ant>(body, m_ants, m_map.primitiveChunkMaps().antMap);

    ptrdiff_t index = m_ants.toBeAdded(ant);

    Ant &refReturn = m_ants.atAddBuffer(index);

    sf::Vector2i homeIndex = refReturn.knowledge().homeChunkIndex();
    auto & objects = m_map.at(homeIndex).ref_antChunk.objects;
    objects.toBeAdded(SpecializedVectorIndexPair<Ant>{&m_ants, index});

    return refReturn;
}

Pheromone &World::preparePheromone(sf::Vector2f position, float size, float mass, const sf::Vector3<unsigned char> &color)
{
    Body body(position, size, mass, color);
    Pheromone pheromone = m_createObject<Pheromone>(body, m_pheromones, m_map.primitiveChunkMaps().pheromoneMap);

    ptrdiff_t index = m_pheromones.toBeAdded(pheromone);

    Pheromone &refReturn = m_pheromones.atAddBuffer(index);

    sf::Vector2i homeIndex = refReturn.knowledge().homeChunkIndex();
    auto & objects = m_map.at(homeIndex).ref_pheromoneChunk.objects;
    objects.toBeAdded(SpecializedVectorIndexPair<Pheromone>{&m_pheromones, index});

    return refReturn;
}

Food &World::prepareFood(sf::Vector2f position, float size, float mass, const sf::Vector3<unsigned char> &color)
{
    Body body(position, size, mass, color);
    Food food = m_createObject<Food>(body, m_food, m_map.primitiveChunkMaps().foodMap);

    ptrdiff_t index = m_food.toBeAdded(food);

    Food &refReturn = m_food.atAddBuffer(index);

    sf::Vector2i homeIndex = refReturn.knowledge().homeChunkIndex();
    auto & objects = m_map.at(homeIndex).ref_foodChunk.objects;
    objects.toBeAdded(SpecializedVectorIndexPair<Food>{&m_food, index});

    return refReturn;
}


