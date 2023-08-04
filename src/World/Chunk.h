#pragma once

#include <vector>
#include <functional>
#include <type_traits>

#include "../Objects/Ant.h"
#include "../Objects/Pheromone.h"
#include "../Objects/Food.h"
#include "../Utils/SpecializedVector.h"

template <class T>
struct SpecializedVectorIndexPair
{
    SpecializedVector<T> *ptrWorldObjects;
    size_t index;
};

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

    SpecializedVector<T> *m_ptrWorldObjects;

public:
    static constexpr unsigned CHUNK_SIZE_X = 64;
    static constexpr unsigned CHUNK_SIZE_Y = 64;

    SpecializedVector<SpecializedVectorIndexPair<T>> objects{Chunk<T>::INIT_CHUNK, Chunk<T>::SWAP_CHUNK};


    Chunk() = default;
    Chunk(sf::Vector2i index, SpecializedVector<T> *ptrWorldObjects);
    Chunk(int x, int y, SpecializedVector<T> *ptrWorldObjects);

    ///TODO: make them only SpecializedVectorIndexPair instead of template
    static void SWAP_CHUNK(SpecializedVectorIndexPair<T> & elem1, size_t atIndex1,
                           SpecializedVectorIndexPair<T> & elem2, size_t atIndex2);

    static void INIT_CHUNK(SpecializedVectorIndexPair<T> & elem, size_t indexChunk);



};


template <class T>
Chunk<T>::Chunk(sf::Vector2i index, SpecializedVector<T> *ptrWorldObjects)
: m_index{index}, m_ptrWorldObjects{ptrWorldObjects}
{

}

template <class T>
Chunk<T>::Chunk(int x, int y, SpecializedVector<T> *ptrWorldObjects) : Chunk(sf::Vector2i(x, y), ptrWorldObjects)
{

}

template <typename T>
void Chunk<T>::SWAP_CHUNK(SpecializedVectorIndexPair<T> &elem1, size_t atIndex1,
                          SpecializedVectorIndexPair<T> &elem2, size_t atIndex2)
{
    //swapping only the index as the reference to the world objects will be the same
    std::swap(elem1, elem2);

    elem1.ptrWorldObjects->at(elem1.index).knowledge().giveChunkIndex(atIndex1);
    elem2.ptrWorldObjects->at(elem1.index).knowledge().giveChunkIndex(atIndex2);
}
template <typename T>
void Chunk<T>::INIT_CHUNK(SpecializedVectorIndexPair<T> &elem, size_t indexChunk)
{
    elem.ptrWorldObjects->at(elem.index).knowledge().giveChunkIndex(indexChunk);
}