#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

#include "Types.h"
class Chunk;

template <class T>
class WorldKnowledge
{

private:
    Chunk *m_pHomeChunk = nullptr;
    RefVector_t<T>::iterator m_chunkIt = {};
public:
    WorldKnowledge() = default;
    explicit WorldKnowledge(Chunk *pHomeChunk) : m_pHomeChunk(pHomeChunk)
    {}
};
