#pragma once

#include <vector>
#include <functional>

#include "GenericObject.h"
#include "Ant.h"
#include "Pheromone.h"
#include "Food.h"
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


    SpecializedVector<Ant*> ants{SpecializedVector<Ant*>::SWAP_CHUNK};
    SpecializedVector<Pheromone*> pheromones{SpecializedVector<Pheromone*>::SWAP_CHUNK};
    SpecializedVector<Food*> food{SpecializedVector<Food*>::SWAP_CHUNK};

};


