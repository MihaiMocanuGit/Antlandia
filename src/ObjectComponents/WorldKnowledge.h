#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

#include "../Utils/Types.h"
template <class T>
class Chunk;

class World;
struct PrimitiveChunkMaps;

template <class T>
class WorldKnowledge
{
    template <typename U>
    friend class SpecializedVector;
private:
    World *m_pWorld = nullptr;
    PrimitiveChunkMap_t<T> *m_pChunkMap = nullptr;
    Chunk<T> *m_pHomeChunk = nullptr;

    size_t m_indexChunk = -1; //size_t max
    size_t m_indexWorld = -1;
public:
    WorldKnowledge() = default;
    explicit WorldKnowledge(World *pWorld, Chunk<T> *pHomeChunk) : m_pWorld(pWorld), m_pHomeChunk(pHomeChunk)
    {}
};
