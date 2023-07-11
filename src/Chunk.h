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
    static const sf::Vector2u CHUNK_SIZE;

    Chunk() = default;
    explicit Chunk(sf::Vector2u index);
    Chunk(unsigned x, unsigned y);


    SpecializedVector<GenericObject*> ants{SpecializedVector<GenericObject*>::SWAP_CHUNK};
    SpecializedVector<GenericObject*> pheromones{SpecializedVector<GenericObject*>::SWAP_CHUNK};
    SpecializedVector<GenericObject*> food{SpecializedVector<GenericObject*>::SWAP_CHUNK};

};


