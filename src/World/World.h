#pragma once
#include "ChunkMap.h"
#include <cassert>
class World
{
private:
    ChunkMap m_map = {};
    SpecializedVector<Ant> m_ants{World::INIT_WORLD, World::SWAP_WORLD};
    SpecializedVector<Pheromone> m_pheromones{World::INIT_WORLD, World::SWAP_WORLD};
    SpecializedVector<Food> m_food{World::INIT_WORLD, World::SWAP_WORLD};

    template <class T>
    T m_createObject(const Body& body, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T>& objectMap);
public:
    World() = default;
    explicit World(sf::Vector2u size);
    World(unsigned sizeX, unsigned sizeY);

    template <typename T>
    static void SWAP_WORLD(T &elem1, size_t atIndex1, T &elem2, size_t atIndex2);
    template <typename T>
    static void INIT_WORLD(T &elem, size_t indexWorld);

    ChunkMap& map();
    SpecializedVector<Ant>& ants();
    const SpecializedVector<Ant>& ants() const;

    SpecializedVector<Pheromone>& pheromones();
    const SpecializedVector<Pheromone>& pheromones() const;

    SpecializedVector<Food>& food();
    const SpecializedVector<Food>& food() const;

    [[nodiscard]] sf::Vector2u size() const;

    Ant& addAnt(sf::Vector2f position, float size = 2, float mass = 1,
                const sf::Vector3<unsigned char> &color = {0, 0, 0});
    Pheromone& addPheromone(sf::Vector2f position, float size = 1, float mass = 1,
                const sf::Vector3<unsigned char> &color = {0, 255, 0});
    Food& addFood(sf::Vector2f position, float size = 1.5, float mass = 1,
                const sf::Vector3<unsigned char> &color = {255, 0, 0});





};

template <class T>
T World::m_createObject(const Body &body, SpecializedVector<T> &worldObjectVector, std::vector<Chunk<T>>& objectMap)
{
    sf::Vector2i chunkIndex = m_map.computeChunkIndex(body.getPosition());

    assert(m_map.isValidIndex(chunkIndex.x, chunkIndex.y));

    WorldKnowledge<T> knowledge(this, &worldObjectVector, &objectMap);
    knowledge.giveHomeChunk(chunkIndex);

    return T{body, knowledge};
}



template <typename T>
void World::SWAP_WORLD(T &elem1, size_t atIndex1, T &elem2, size_t atIndex2)
{
    std::swap(elem1, elem2);

    elem1.knowledge().giveWorldIndex(atIndex1);
    elem2.knowledge().giveWorldIndex(atIndex2);
}
template <typename T>
void World::INIT_WORLD(T &elem, size_t indexWorld)
{
    elem.knowledge().giveWorldIndex(indexWorld);
}