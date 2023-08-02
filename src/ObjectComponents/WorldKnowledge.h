#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

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
    friend class World;
private:

    World *m_pWorld = nullptr;
    SpecializedVector<T> *m_pWorldObjectVector = nullptr;


    PrimitiveChunkMap_t<T> *m_pPrimitiveChunkMap = nullptr;
    sf::Vector2i m_homeChunkIndexes = sf::Vector2i {-1, -1};

    bool m_worldIndexWasGiven = false;
    size_t m_indexWorld = -1; //size_t max

    bool m_chunkIndexWasGiven = false;
    size_t m_indexChunk = -1; //size_t max


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

    void giveWorldIndex(const size_t& indexInWorldVector);
    void giveChunkIndex(const size_t& indexInChunkVector);

    void giveChunkData(const sf::Vector2i &homeChunkIndexes, const size_t& indexInChunkVector);

    World & world();
};

template <class T>
void WorldKnowledge<T>::giveChunkIndex(const size_t &indexInChunkVector)
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
void WorldKnowledge<T>::giveWorldIndex(const size_t &indexInWorldVector)
{
    //TODO: assert index validity
    m_indexWorld = indexInWorldVector;

    m_worldIndexWasGiven = true;
}

template <class T>
void WorldKnowledge<T>::giveChunkData(const sf::Vector2i &homeChunkIndexes, const size_t &indexInChunkVector)
{
    //TODO: assert index/homeChunk validity
    m_homeChunkIndexes = homeChunkIndexes;
    m_indexChunk = indexInChunkVector;

    m_worldIndexWasGiven = true;
}


