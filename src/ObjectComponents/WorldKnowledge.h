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

    bool m_worldIndexWasGiven = false;
    ptrdiff_t m_indexInWorld = PTRDIFF_MAX;

    PrimitiveChunkMap_t<T> *m_pPrimitiveChunkMap = nullptr;

    bool m_homeChunkWasGiven = false;
    sf::Vector2i m_homeChunkIndexes = sf::Vector2i {-1, -1};
    bool m_indexInHomeChunkWasGiven = false;
    ptrdiff_t m_indexInHomeChunk = PTRDIFF_MAX;

    bool m_nextChunkWasGiven = false;
    sf::Vector2i m_nextChunkIndexes = sf::Vector2i {-1, -1};
    bool m_indexInNextChunkWasGiven = false;
    ptrdiff_t m_indexInNextChunk = PTRDIFF_MAX;
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

    void giveIndexInWorld(const ptrdiff_t& indexInWorldVector);
    void removeWorldInfo();


    void giveHomeChunk(const sf::Vector2i &homeChunkIndexes);
    void giveIndexInHomeChunk(const ptrdiff_t& indexInChunkVector);
    void removeIndexInHomeChunk();
    void removeHomeChunkInfo();

    void giveNextChunk(const sf::Vector2i &nextChunkIndexes);
    void giveIndexInNextChunk(const ptrdiff_t& indexInNextChunkVector);
    void removeIndexInNextChunk();
    void removeNextChunkInfo();

    void updateHomeChunkWithNext();

    World & world();
    SpecializedVector<T> *pWorldObjectVector();
    ptrdiff_t indexInWorld() const;

    PrimitiveChunkMap_t<T> & primitiveChunkMap();
    sf::Vector2i homeChunkIndexes() const;
    ptrdiff_t indexInHomeChunk() const;
    bool existsInHomeChunk() const;

    sf::Vector2i nextChunkIndexes() const;
    ptrdiff_t indexInNextChunk() const;
    bool willBeAddedInNextChunk() const;
};

template <class T>
ptrdiff_t WorldKnowledge<T>::indexInNextChunk() const
{
    return m_indexInNextChunk;
}

template <class T>
sf::Vector2i WorldKnowledge<T>::nextChunkIndexes() const
{
    return m_nextChunkIndexes;
}

template <class T>
void WorldKnowledge<T>::removeIndexInNextChunk()
{
    m_indexInHomeChunkWasGiven = false;
    m_indexInHomeChunk = PTRDIFF_MAX;
}

template <class T>
void WorldKnowledge<T>::removeIndexInHomeChunk()
{
    m_indexInHomeChunkWasGiven = false;
    m_indexInHomeChunk = PTRDIFF_MAX;
}

template <class T>
bool WorldKnowledge<T>::willBeAddedInNextChunk() const
{
    return m_nextChunkWasGiven;
}

template <class T>
void WorldKnowledge<T>::updateHomeChunkWithNext()
{
    m_homeChunkWasGiven = m_nextChunkWasGiven;
    m_homeChunkIndexes = m_nextChunkIndexes;

    m_indexInHomeChunkWasGiven = m_indexInNextChunkWasGiven;
    m_indexInHomeChunk = m_indexInNextChunk;
}

template <class T>
void WorldKnowledge<T>::removeNextChunkInfo()
{
    removeIndexInNextChunk();

    m_nextChunkWasGiven = false;
    m_nextChunkIndexes = {-1, -1};
}

template <class T>
void WorldKnowledge<T>::giveIndexInNextChunk(const ptrdiff_t &indexInNextChunkVector)
{
    m_indexInNextChunk = indexInNextChunkVector;
    m_indexInNextChunkWasGiven = true;
}

template <class T>
void WorldKnowledge<T>::giveNextChunk(const sf::Vector2i &nextChunkIndexes)
{

    m_nextChunkIndexes = nextChunkIndexes;

    m_nextChunkWasGiven = true;
}

template <class T>
void WorldKnowledge<T>::removeHomeChunkInfo()
{
    removeIndexInHomeChunk();

    m_homeChunkWasGiven = false;
    m_homeChunkIndexes = {-1, -1};
}

template <class T>
void WorldKnowledge<T>::removeWorldInfo()
{
    m_worldIndexWasGiven = false;
    m_indexInWorld = PTRDIFF_MAX;
}

template <class T>
SpecializedVector<T> *WorldKnowledge<T>::pWorldObjectVector()
{
    return m_pWorldObjectVector;
}

template <class T>
bool WorldKnowledge<T>::existsInHomeChunk() const
{
    return m_indexInHomeChunkWasGiven;
}

template <class T>
ptrdiff_t WorldKnowledge<T>::indexInHomeChunk() const
{
    return m_indexInHomeChunk;
}

template <class T>
ptrdiff_t WorldKnowledge<T>::indexInWorld() const
{
    return m_indexInWorld;
}

template <class T>
PrimitiveChunkMap_t<T> &WorldKnowledge<T>::primitiveChunkMap()
{
    return *m_pPrimitiveChunkMap;
}

template <class T>
sf::Vector2i WorldKnowledge<T>::homeChunkIndexes() const
{
    return m_homeChunkIndexes;
}


template <class T>
void WorldKnowledge<T>::giveIndexInHomeChunk(const ptrdiff_t &indexInChunkVector)
{
    //TODO: assert index validity
    m_indexInHomeChunk = indexInChunkVector;

    m_indexInHomeChunkWasGiven = true;
}

template <class T>
World &WorldKnowledge<T>::world()
{
    return *m_pWorld;
}

template <class T>
void WorldKnowledge<T>::giveIndexInWorld(const ptrdiff_t &indexInWorldVector)
{
    //TODO: assert index validity
    m_indexInWorld = indexInWorldVector;

    m_worldIndexWasGiven = true;
}

template <class T>
void WorldKnowledge<T>::giveHomeChunk(const sf::Vector2i &homeChunkIndexes)
{
    //TODO: assert index of homeChunk validity
    m_homeChunkIndexes = homeChunkIndexes;

    m_homeChunkWasGiven = true;
}


