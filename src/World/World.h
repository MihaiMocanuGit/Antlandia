#pragma once
#include "ChunkMap.h"
#include "../Utils/Utils.h"
#include "../WorldActions/ObjectMover.h"

#include <cassert>

class World
{
private:
    ChunkMap m_map = {};
    SpecializedVector<Ant> m_ants{INIT_ADD_WORLD, INIT_REMOVE_WORLD, INIT_FINALISE_WORLD, SWAP_WORLD, DESTRUCT_WORLD};
    SpecializedVector<Pheromone> m_pheromones{INIT_ADD_WORLD, INIT_REMOVE_WORLD, INIT_FINALISE_WORLD, SWAP_WORLD, DESTRUCT_WORLD};
    SpecializedVector<Food> m_food{INIT_ADD_WORLD, INIT_REMOVE_WORLD, INIT_FINALISE_WORLD, SWAP_WORLD, DESTRUCT_WORLD};

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
        ptrdiff_t indexInChunk = knowledge.indexInHomeChunk();
        homeChunk.objects.at(indexInChunk).index = newIndex;

    }
public:
    World() = default;
    explicit World(sf::Vector2u size);
    World(unsigned sizeX, unsigned sizeY);


    template <typename T>
    static void INIT_ADD_WORLD(T &elem, ptrdiff_t indexWorld);
    template <typename T>
    static void INIT_REMOVE_WORLD(T &elem, ptrdiff_t indexWorld);
    template <typename T>
    static void INIT_FINALISE_WORLD(T &elem, ptrdiff_t indexWorld);
    template <typename T>
    static void SWAP_WORLD(T &elem1, ptrdiff_t atIndex1, T &elem2, ptrdiff_t atIndex2);
    template <typename T>
    static void DESTRUCT_WORLD(T &elem, ptrdiff_t indexWorld);


    ChunkMap& map();

    template <class T>
    void moveTo(GenericObject<T> &object, const sf::Vector2f &newPosition);

    template <class T>
    void moveBy(GenericObject<T> &object, const sf::Vector2f &newPosition);


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
    std::swap(elem1, elem2);

    //in a chunk we have a vector of indexes pointing to the index of said element
    //in the World vector. As such, if the position of an element in the world vector
    //is changed, we need to update the chunk vector too.
    WorldKnowledge<T> &r_knowledge1 = elem1.knowledge();
    if (r_knowledge1.existsInHomeChunk() or r_knowledge1.willBeAddedInNextChunk())
        m_updateChunkVectorInfo(elem1, atIndex1);
    r_knowledge1.giveIndexInWorld(atIndex1);

    WorldKnowledge<T> &r_knowledge2 = elem2.knowledge();
    if (r_knowledge2.existsInHomeChunk() or r_knowledge2.willBeAddedInNextChunk())
        m_updateChunkVectorInfo(elem2, atIndex2);
    r_knowledge2.giveIndexInWorld(atIndex2);


}
template <typename T>
void World::INIT_FINALISE_WORLD(T &elem, ptrdiff_t indexWorld)
{
    WorldKnowledge<T> &r_knowledge = elem.knowledge();
    if (r_knowledge.existsInHomeChunk() or r_knowledge.willBeAddedInNextChunk())
        m_updateChunkVectorInfo(elem, indexWorld);

    r_knowledge.giveIndexInWorld(indexWorld);


}


template <typename T>
void World::DESTRUCT_WORLD(T &elem, ptrdiff_t indexWorld)
{
    WorldKnowledge<T> &r_knowledge = elem.knowledge();
    r_knowledge.removeHomeChunkInfo();
    r_knowledge.removeNextChunkInfo();
    r_knowledge.removeWorldInfo();
}



template <class T>
void World::moveBy(GenericObject<T> &object, const sf::Vector2f &newPosition)
{
    assert (object.knowledge().existsInHomeChunk());
    ObjectMover<T> mover(m_map);
    mover.moveBy(object, newPosition);
}

template <class T>
void World::moveTo(GenericObject<T> &object, const sf::Vector2f &newPosition)
{
    assert (object.knowledge().existsInHomeChunk());
    ObjectMover<T> mover(m_map);
    mover.moveTo(object, newPosition);
}

