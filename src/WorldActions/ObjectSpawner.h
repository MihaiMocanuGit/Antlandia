#pragma once
#include "../World/World.h"
#include "../Utils/Utils.h"
class ObjectSpawner
{
private:
    ChunkMap &m_r_map;
    /// \brief
    /// \tparam T must be constructable from a GenericObject, T{GenericObject} must be valid.
    /// \param body
    /// \param worldObjectVector
    /// \param objectMap
    /// \return
    template <class T>
    T m_createObject(const Body& body, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T>& objectMap);
    template <class T>
    T& m_prepareObjectIntoWorld(const T& object, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T> &objectMap);

    template <class T>
    static void m_syncHomeChunkVectorInfoWithWorld(T& elem, size_t newIndex);
    template <class T>
    static void m_syncNextChunkVectorInfoWithWorld(T& elem, size_t newIndex);

public:
    explicit ObjectSpawner(ChunkMap &r_map);

    template <class T>
    T& prepareObject(const Body& body, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T>& objectMap);
    template <class T>
    T& prepareObject(const T& object, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T>& objectMap);
};

template <class T>
void ObjectSpawner::m_syncHomeChunkVectorInfoWithWorld(T &elem, size_t newIndex)
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
void ObjectSpawner::m_syncNextChunkVectorInfoWithWorld(T &elem, size_t newIndex)
{
    WorldKnowledge<T> &r_knowledge = elem.knowledge();
    sf::Vector2i nextChunkIndexes = r_knowledge.nextChunkIndexes();
    size_t linearNextChunkIndex = xyToIndex(nextChunkIndexes.x, nextChunkIndexes.y, r_knowledge.world().size().x);

    Chunk<T> &r_next = r_knowledge.primitiveChunkMap().at(linearNextChunkIndex);
    ptrdiff_t indexInChunk = r_knowledge.indexInNextChunk();
    auto &r_chunkElement = r_next.objects.at(indexInChunk);
    r_chunkElement.index = newIndex;
}

template <class T>
T ObjectSpawner::m_createObject(const Body &body, SpecializedVector<T> &worldObjectVector, std::vector<Chunk<T>>& objectMap)
{
    sf::Vector2i chunkIndex = m_r_map.computeChunkIndex(body.getPosition());
    assert(m_r_map.isValidIndex(chunkIndex.x, chunkIndex.y));

    WorldKnowledge<T> knowledge(this, &worldObjectVector, &objectMap);

    return T{body, knowledge};
}
template <class T>
T &ObjectSpawner::m_prepareObjectIntoWorld(const T &object, SpecializedVector<T> &worldObjectVector,
                                   PrimitiveChunkMap_t<T> &objectMap)
{
    //insert into World Vector
    ptrdiff_t indexInWorld = worldObjectVector.toBeAdded(object);
    T &r_addedObject = worldObjectVector.at(indexInWorld);
    assert(r_addedObject.knowledge().indexInWorld() == indexInWorld);

    //Give the chunk into which it will be inserted (as it cannot be done within the custom specialized vector functions)
    sf::Vector2i nextChunkIndexes = m_r_map.computeChunkIndex(object.body().getPosition());
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
T& ObjectSpawner::prepareObject(const Body &body, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T> &objectMap)
{
    T object = m_createObject<T>(body, worldObjectVector, objectMap);

    return m_prepareObjectIntoWorld(object, worldObjectVector, objectMap);
}

template <class T>
T &ObjectSpawner::prepareObject(const T &object, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T> &objectMap)
{
    return m_prepareObjectIntoWorld(object, worldObjectVector, objectMap);
}

