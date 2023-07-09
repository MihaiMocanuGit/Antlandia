#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

#include "Types.h"
class Chunk;

template <class T>
class WorldKnowledge
{
    friend class ChunkContainer;
private:
    Chunk *m_pHomeChunk = nullptr;
    size_t m_indexChunk = -1; //size_t max
    size_t m_indexWorld = -1;
public:
    WorldKnowledge() = default;
    explicit WorldKnowledge(Chunk *pHomeChunk) : m_pHomeChunk(pHomeChunk)
    {}
};
