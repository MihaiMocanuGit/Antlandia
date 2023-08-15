#pragma once
#include "../World/ChunkMap.h"
#include "../Utils/Utils.h"
class ObjectSpawner
{
private:
    World* const m_pWorld;
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



public:
    explicit ObjectSpawner(World* pWorld, ChunkMap &r_map);

    template <class T>
    T& prepareObject(const Body& body, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T>& objectMap);
    template <class T>
    T& prepareObject(const T& object, SpecializedVector<T> &worldObjectVector, PrimitiveChunkMap_t<T>& objectMap);
};


template <class T>
T ObjectSpawner::m_createObject(const Body &body, SpecializedVector<T> &worldObjectVector, std::vector<Chunk<T>>& objectMap)
{
    sf::Vector2i chunkIndex = m_r_map.computeChunkIndex(body.getPosition());
    assert(m_r_map.isValidIndex(chunkIndex.x, chunkIndex.y));

    WorldKnowledge<T> knowledge(m_pWorld, &worldObjectVector, &objectMap);

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

