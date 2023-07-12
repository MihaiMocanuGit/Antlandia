#pragma once
#include "ChunkMap.h"

class World
{
private:
    ChunkMap m_map = {};
    SpecializedVector<Ant> m_ants{SpecializedVector<Ant>::SWAP_WORLD};
    SpecializedVector<Pheromone> m_pheromones{SpecializedVector<Pheromone>::SWAP_WORLD};
    SpecializedVector<Food> m_food{SpecializedVector<Food>::SWAP_WORLD};

    template <class T>
    T m_createObject(const Body& body);
public:
    World() = default;
    explicit World(sf::Vector2u size);
    World(unsigned sizeX, unsigned sizeY);

    ChunkMap& map();
    SpecializedVector<Ant>& ants();
    SpecializedVector<Pheromone>& pheromones();
    SpecializedVector<Food>& food();

    [[nodiscard]] sf::Vector2u size() const;

    Ant& addAnt(sf::Vector2f position, float size = 1, float mass = 1,
                const sf::Vector3<unsigned char> &color = {0, 0, 0});
    Pheromone& addPheromone(sf::Vector2f position, float size = 0.5, float mass = 1,
                const sf::Vector3<unsigned char> &color = {0, 255, 0});
    Food& addFood(sf::Vector2f position, float size = 1, float mass = 1,
                const sf::Vector3<unsigned char> &color = {0, 0, 0});





};

template <class T>
T World::m_createObject(const Body &body)
{
    sf::Vector2i chunkIndex = m_map.computeHomeChunk(body.getPosition());
    Chunk *ptrHome = &m_map.at(chunkIndex);
    WorldKnowledge knowledge(this, ptrHome);
    GenericObject genericObject(body, knowledge);

    return T{genericObject};
}


