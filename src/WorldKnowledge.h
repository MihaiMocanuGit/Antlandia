#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

#include "Types.h"
class Chunk;
class World;

class WorldKnowledge
{
    template <typename T>
    friend class SpecializedVector;
private:
    World *m_pWorld = nullptr;
    Chunk *m_pHomeChunk = nullptr;

    size_t m_indexChunk = -1; //size_t max
    size_t m_indexWorld = -1;
public:
    WorldKnowledge() = default;
    explicit WorldKnowledge(World *pWorld, Chunk *pHomeChunk) : m_pWorld(pWorld), m_pHomeChunk(pHomeChunk)
    {}
};
