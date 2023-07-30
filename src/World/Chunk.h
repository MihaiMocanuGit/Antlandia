#pragma once

#include <vector>
#include <functional>

#include "../Objects/Ant.h"
#include "../Objects/Pheromone.h"
#include "../Objects/Food.h"
#include "../Utils/SpecializedVector.h"

template <class T>
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
    static constexpr unsigned CHUNK_SIZE_X = 64;
    static constexpr unsigned CHUNK_SIZE_Y = 64;

    Chunk() = default;
    explicit Chunk(sf::Vector2u index);
    Chunk(unsigned x, unsigned y);


    SpecializedVector<T*> objects{SpecializedVector<T*>::INIT_CHUNK, SpecializedVector<T*>::SWAP_CHUNK};


};


template <class T>
Chunk<T>::Chunk(sf::Vector2u index) : m_index{index}
{

}

template <class T>
Chunk<T>::Chunk(unsigned int x, unsigned int y) : Chunk(sf::Vector2u(x, y))
{

}
