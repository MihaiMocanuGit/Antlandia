#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cstdint>

#include "../Utils/Types.h"
template <class T>
class Chunk;

template <typename U>
class SpecializedVector;

class World;
class ChunkMap;
struct PrimitiveChunkMaps;

template <class T>
class WorldKnowledge
{
private:

    World *m_pWorld = nullptr;
    SpecializedVector<T> *m_pWorldObjectVector = nullptr;


    PrimitiveChunkMap_t<T> *m_pPrimitiveChunkMap = nullptr;
    sf::Vector2i m_homeChunkIndexes = sf::Vector2i {-1, -1};

    bool m_worldIndexWasGiven = false;
    ptrdiff_t m_indexWorld = PTRDIFF_MAX;

    bool m_chunkIndexWasGiven = false;
    ptrdiff_t m_indexChunk = PTRDIFF_MAX;


public:
    WorldKnowledge() = default;

    /// \brief
    /// \param pWorld
    /// \param pSpecializedVector
    /// \param pPrimitiveChunkMap
    /// \param pHomeChunk
    /// \note You must give vector indexes after the object is completely inserted into the world
    WorldKnowledge(World *pWorld, SpecializedVector<T> *pSpecializedVector,
                   PrimitiveChunkMap_t<T> *pPrimitiveChunkMap)
                   : m_pWorld(pWorld), m_pWorldObjectVector(pSpecializedVector),
                   m_pPrimitiveChunkMap(pPrimitiveChunkMap)
    {}

    void giveWorldIndex(const ptrdiff_t& indexInWorldVector);
    void removeWorldInfo();

    void giveChunkIndex(const ptrdiff_t& indexInChunkVector);
    void removeChunkInfo();

    void giveHomeChunk(const sf::Vector2i &homeChunkIndexes);

    World & world();
    SpecializedVector<T> *pWorldObjectVector();
    ptrdiff_t indexInWorld() const;

    PrimitiveChunkMap_t<T> & primitiveChunkMap();
    sf::Vector2i homeChunkIndex() const;
    ptrdiff_t indexInChunk() const;
    bool existsInChunk() const;
};

template <class T>
void WorldKnowledge<T>::removeChunkInfo()
{
    m_chunkIndexWasGiven = false;
    m_indexChunk = PTRDIFF_MAX;
    m_homeChunkIndexes = {-1, -1};

}

template <class T>
void WorldKnowledge<T>::removeWorldInfo()
{
    m_worldIndexWasGiven = false;
    m_indexWorld = PTRDIFF_MAX;
}

template <class T>
SpecializedVector<T> *WorldKnowledge<T>::pWorldObjectVector()
{
    return m_pWorldObjectVector;
}

template <class T>
bool WorldKnowledge<T>::existsInChunk() const
{
    return m_chunkIndexWasGiven;
}

template <class T>
ptrdiff_t WorldKnowledge<T>::indexInChunk() const
{
    return m_indexChunk;
}

template <class T>
ptrdiff_t WorldKnowledge<T>::indexInWorld() const
{
    return m_indexWorld;
}

template <class T>
PrimitiveChunkMap_t<T> &WorldKnowledge<T>::primitiveChunkMap()
{
    return *m_pPrimitiveChunkMap;
}

template <class T>
sf::Vector2i WorldKnowledge<T>::homeChunkIndex() const
{
    return m_homeChunkIndexes;
}


template <class T>
void WorldKnowledge<T>::giveChunkIndex(const ptrdiff_t &indexInChunkVector)
{
    //TODO: assert index validity
    m_indexChunk = indexInChunkVector;

    m_chunkIndexWasGiven = true;
}

template <class T>
World &WorldKnowledge<T>::world()
{
    return *m_pWorld;
}

template <class T>
void WorldKnowledge<T>::giveWorldIndex(const ptrdiff_t &indexInWorldVector)
{
    //TODO: assert index validity
    m_indexWorld = indexInWorldVector;

    m_worldIndexWasGiven = true;
}

template <class T>
void WorldKnowledge<T>::giveHomeChunk(const sf::Vector2i &homeChunkIndexes)
{
    //TODO: assert index of homeChunk validity
    m_homeChunkIndexes = homeChunkIndexes;
}


