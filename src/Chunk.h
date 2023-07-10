#pragma once

#include <vector>
#include <functional>

#include "GenericObject.h"
#include "Ant.h"
#include "ChunkContainer.h"
class Chunk
{
    friend class ChunkMap;
private:

    sf::Vector2i m_index = {-1, -1};

    /// \brief
    /// UpperLeft   UpperMid    UpperRight\n
    /// Left        Itself       Right\n
    /// LowerLeft   LowerMid     LowerRight
    Chunk *m_neighbours[3][3] = {{nullptr, nullptr, nullptr},
                                 {nullptr, this, nullptr},
                                 {nullptr, nullptr, nullptr}};
public:
    Chunk() = default;
    explicit Chunk(sf::Vector2u index);
    Chunk(unsigned x, unsigned y);

    static const sf::Vector2i CHUNK_SIZE;
    ChunkContainer ants;
    ChunkContainer pheromones;
    ChunkContainer food;

};


