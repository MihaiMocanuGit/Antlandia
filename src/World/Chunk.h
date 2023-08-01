#pragma once

#include <vector>
#include <functional>
#include <type_traits>

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

    template <class U>
    static void SWAP_CHUNK(U & elem1, size_t atIndex1,
                           U & elem2, size_t atIndex2);

    template <class U>
    static void INIT_CHUNK(U & elem, size_t indexChunk);

    SpecializedVector<T*> objects{Chunk<T>::INIT_CHUNK<T*>, Chunk<T>::SWAP_CHUNK<T*>};


};


template <class T>
Chunk<T>::Chunk(sf::Vector2u index) : m_index{index}
{

}

template <class T>
Chunk<T>::Chunk(unsigned int x, unsigned int y) : Chunk(sf::Vector2u(x, y))
{

}

template <typename T>
template <typename U>
void Chunk<T>::SWAP_CHUNK(U &elem1, size_t atIndex1, U &elem2, size_t atIndex2)
{
    static_assert(std::is_same<T*,U>::value);

    std::swap(elem1, elem2);

    elem1->knowledge().m_indexChunk = atIndex1;
    elem2->knowledge().m_indexChunk = atIndex2;
}
template <typename T>
template <typename U>
void Chunk<T>::INIT_CHUNK(U &elem, size_t indexChunk)
{
    static_assert(std::is_same<T*,U>::value);

    sf::Vector2f position = elem->body().getPosition();
    sf::Vector2i homeChunkIndex = elem->knowledge().world().map().computeChunkIndex(position);

    elem->knowledge().giveChunkData(homeChunkIndex, indexChunk);
}