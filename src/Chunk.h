#pragma once

#include <vector>
#include <functional>

#include "GenericObject.h"
#include "Ant.h"
#include "SpecializedVector.h"
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
    static constexpr unsigned CHUNK_SIZE_X = 32;
    static constexpr unsigned CHUNK_SIZE_Y = 32;

    Chunk() = default;
    explicit Chunk(sf::Vector2u index);
    Chunk(unsigned x, unsigned y);


    SpecializedVector<GenericObject*> ants{SpecializedVector<GenericObject*>::SWAP_CHUNK};
    SpecializedVector<GenericObject*> pheromones{SpecializedVector<GenericObject*>::SWAP_CHUNK};
    SpecializedVector<GenericObject*> food{SpecializedVector<GenericObject*>::SWAP_CHUNK};

};


