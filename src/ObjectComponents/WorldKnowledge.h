#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

#include "../Utils/Types.h"
template <class T>
class Chunk;

template <typename U>
class SpecializedVector;

class World;
struct PrimitiveChunkMaps;

template <class T>
class WorldKnowledge
{
    template <typename U>
    friend class SpecializedVector;
private:

    World *m_pWorld = nullptr;
    SpecializedVector<T> *m_pWorldObjectVector = nullptr;


    PrimitiveChunkMap_t<T> *m_pPrimitiveChunkMap = nullptr;
    Chunk<T> *m_pHomeChunk = nullptr;

    bool m_indexesWereGiven = false;
    size_t m_indexWorld = -1; //size_t max
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

    void giveVectorIndexes(const size_t& indexInWorldVector, Chunk<T> *pHomeChunk, const size_t& indexInChunkVector);
    void changeHomeChunk(Chunk<T> *pHomeChunk, const size_t& indexInChunkVector);
};
