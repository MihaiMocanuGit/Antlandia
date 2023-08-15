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
    T& m_prepareObjectIntoWorld(const T& object, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T> &objectMap);

    template <class T>
    static void m_syncHomeChunkVectorInfoWithWorld(T& elem, size_t newIndex)
    {
        WorldKnowledge<T> &r_knowledge = elem.knowledge();
        sf::Vector2i homeChunkIndexes = r_knowledge.homeChunkIndexes();
        size_t linearHomeChunkIndex = xyToIndex(homeChunkIndexes.x, homeChunkIndexes.y, r_knowledge.world().size().x);

        Chunk<T> &r_home = r_knowledge.primitiveChunkMap().at(linearHomeChunkIndex);
        ptrdiff_t indexInChunk = r_knowledge.indexInHomeChunk();
        auto &r_chunkElement = r_home.objects.at(indexInChunk);
        r_chunkElement.index = newIndex;
    }

    template <class T>
    static void m_syncNextChunkVectorInfoWithWorld(T& elem, size_t newIndex)
    {
        WorldKnowledge<T> &r_knowledge = elem.knowledge();
        sf::Vector2i nextChunkIndexes = r_knowledge.nextChunkIndexes();
        size_t linearNextChunkIndex = xyToIndex(nextChunkIndexes.x, nextChunkIndexes.y, r_knowledge.world().size().x);

        Chunk<T> &r_next = r_knowledge.primitiveChunkMap().at(linearNextChunkIndex);
        ptrdiff_t indexInChunk = r_knowledge.indexInNextChunk();
        auto &r_chunkElement = r_next.objects.at(indexInChunk);
        r_chunkElement.index = newIndex;
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
    void moveBy(GenericObject<T> &object, const sf::Vector2f &moveByOffset);


    SpecializedVector<Ant>& ants();
    const SpecializedVector<Ant>& ants() const;

    SpecializedVector<Pheromone>& pheromones();
    const SpecializedVector<Pheromone>& pheromones() const;

    SpecializedVector<Food>& food();
    const SpecializedVector<Food>& food() const;

    [[nodiscard]] sf::Vector2u size() const;

    template <class T>
    T& prepareObject(const Body& body, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T>& objectMap);

    template <class T>
    T& prepareObject(const T& object, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T>& objectMap);

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

    return T{body, knowledge};
}
template <class T>
T &World::m_prepareObjectIntoWorld(const T &object, SpecializedVector<T> &worldObjectVector,
                                   PrimitiveChunkMap_t<T> &objectMap)
{
    //insert into World Vector
    ptrdiff_t indexInWorld = worldObjectVector.toBeAdded(object);
    T &r_addedObject = worldObjectVector.at(indexInWorld);
    assert(r_addedObject.knowledge().indexInWorld() == indexInWorld);

    //Give the chunk into which it will be inserted (as it cannot be done within the custom specialized vector functions)
    sf::Vector2i nextChunkIndexes = m_map.computeChunkIndex(object.body().getPosition());
    r_addedObject.knowledge().giveNextChunk(nextChunkIndexes);

    //Mark for insertion the object into the chunk;
    WorldKnowledge<T> &r_knowledge = r_addedObject.knowledge();
    size_t linearNextChunkIndex = xyToIndex(nextChunkIndexes.x, nextChunkIndexes.y, r_knowledge.world().size().x);

    Chunk<T> &r_nextChunk = objectMap.at(linearNextChunkIndex);
    SpecializedVectorIndexPair<T> chunkElem{&worldObjectVector, indexInWorld};
    r_nextChunk.objects.toBeAdded(chunkElem);

    return r_addedObject;
}


template <class T>
T& World::prepareObject(const Body &body, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T> &objectMap)
{
    T object = m_createObject<T>(body, worldObjectVector, objectMap);

    return m_prepareObjectIntoWorld(object, worldObjectVector, objectMap);
}

template <class T>
T &World::prepareObject(const T &object, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T> &objectMap)
{
    return m_prepareObjectIntoWorld(object, worldObjectVector, objectMap);
}


template <typename T>
void World::INIT_ADD_WORLD(T &elem, ptrdiff_t indexWorld)
{
    WorldKnowledge<T> &r_knowledge = elem.knowledge();
    r_knowledge.giveIndexInWorld(indexWorld);

    //at this point the element should not exist in a chunk
    assert(not r_knowledge.willAppearInHomeChunk());
    assert(not r_knowledge.willAppearInNewChunk());
}

template <typename T>
void World::INIT_REMOVE_WORLD(T &elem, ptrdiff_t indexWorld)
{

}

template <typename T>
void World::INIT_FINALISE_WORLD(T &elem, ptrdiff_t indexWorld)
{
    WorldKnowledge<T> &r_knowledge = elem.knowledge();
    r_knowledge.giveIndexInWorld(indexWorld);

    if (r_knowledge.willAppearInHomeChunk())
        m_syncHomeChunkVectorInfoWithWorld(elem, indexWorld);
    if (r_knowledge.willAppearInNewChunk())
        m_syncNextChunkVectorInfoWithWorld(elem, indexWorld);
}


template <typename T>
void World::SWAP_WORLD(T &elem1, ptrdiff_t atIndex1, T &elem2, ptrdiff_t atIndex2)
{
    std::swap(elem1, elem2);

    //in a chunk we have a vector of indexes pointing to the index of said element
    //in the World vector. As such, if the position of an element in the world vector
    //is changed, we need to update the chunk vector too.
    WorldKnowledge<T> &r_knowledge1 = elem1.knowledge();
    r_knowledge1.giveIndexInWorld(atIndex1);
    if (r_knowledge1.willAppearInHomeChunk())
        m_syncHomeChunkVectorInfoWithWorld(elem1, atIndex1);
    if (r_knowledge1.willAppearInNewChunk())
        m_syncNextChunkVectorInfoWithWorld(elem1, atIndex1);

    WorldKnowledge<T> &r_knowledge2 = elem2.knowledge();
    r_knowledge2.giveIndexInWorld(atIndex2);
    if (r_knowledge2.willAppearInHomeChunk())
        m_syncHomeChunkVectorInfoWithWorld(elem2, atIndex2);
    if (r_knowledge2.willAppearInNewChunk())
        m_syncNextChunkVectorInfoWithWorld(elem2, atIndex2);

}

template <typename T>
void World::DESTRUCT_WORLD(T &elem, ptrdiff_t indexWorld)
{
    WorldKnowledge<T> &r_knowledge = elem.knowledge();
    //TODO: Maybe call remove on chunks too? We would need access to remove from the addBuffer

}



template <class T>
void World::moveBy(GenericObject<T> &object, const sf::Vector2f &moveByOffset)
{
    assert (object.knowledge().willAppearInHomeChunk());
    static ObjectMover<T> mover(m_map);
    mover.moveBy(object, moveByOffset);
}

template <class T>
void World::moveTo(GenericObject<T> &object, const sf::Vector2f &newPosition)
{
    assert (object.knowledge().willAppearInHomeChunk());
    static ObjectMover<T> mover(m_map);
    mover.moveTo(object, newPosition);
}

