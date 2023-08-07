#pragma once
#include "ChunkMap.h"
#include "../Utils/Utils.h"

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

    template <class T>
    static void m_updateChunkVectorInfo(T& elem, size_t newIndex)
    {
        WorldKnowledge<T> &knowledge = elem.knowledge();
        sf::Vector2u worldSize = knowledge.world().size();
        sf::Vector2i homeChunkXyIndexes = knowledge.homeChunkIndex();

        size_t homeIndex = xyToIndex(homeChunkXyIndexes.x, homeChunkXyIndexes.y, worldSize.x);
        Chunk<T> &homeChunk = knowledge.primitiveChunkMap().at(homeIndex);
        ptrdiff_t indexInChunk = knowledge.indexInChunk();
        homeChunk.objects.at(indexInChunk).index = newIndex;

    }
public:
    World() = default;
    explicit World(sf::Vector2u size);
    World(unsigned sizeX, unsigned sizeY);

    template <typename T>
    static void SWAP_WORLD(T &elem1, ptrdiff_t atIndex1, T &elem2, ptrdiff_t atIndex2);
    template <typename T>
    static void INIT_WORLD(T &elem, ptrdiff_t indexWorld);

    ChunkMap& map();
    SpecializedVector<Ant>& ants();
    const SpecializedVector<Ant>& ants() const;

    SpecializedVector<Pheromone>& pheromones();
    const SpecializedVector<Pheromone>& pheromones() const;

    SpecializedVector<Food>& food();
    const SpecializedVector<Food>& food() const;

    [[nodiscard]] sf::Vector2u size() const;

    Ant& prepareAnt(sf::Vector2f position, float size = 2, float mass = 1,
                    const sf::Vector3<unsigned char> &color = {0, 0, 0});
    Pheromone& preparePheromone(sf::Vector2f position, float size = 1, float mass = 1,
                                const sf::Vector3<unsigned char> &color = {0, 255, 0});
    Food& prepareFood(sf::Vector2f position, float size = 1.5, float mass = 1,
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
void World::SWAP_WORLD(T &elem1, ptrdiff_t atIndex1, T &elem2, ptrdiff_t atIndex2)
{
    //in a chunk we have a vector of indexes pointing to the index of said element
    //in the World vector. As such, if the position of an element in the world vector
    //is changed, we need to update the chunk vector too.
    if (elem1.knowledge().existsInChunk())
        m_updateChunkVectorInfo(elem1, atIndex2);
    elem1.knowledge().giveWorldIndex(atIndex2);

    if (elem2.knowledge().existsInChunk())
        m_updateChunkVectorInfo(elem2, atIndex1);
    elem2.knowledge().giveWorldIndex(atIndex1);

    std::swap(elem1, elem2);
}
template <typename T>
void World::INIT_WORLD(T &elem, ptrdiff_t indexWorld)
{
    if (elem.knowledge().existsInChunk())
        m_updateChunkVectorInfo(elem, indexWorld);

    elem.knowledge().giveWorldIndex(indexWorld);


}


