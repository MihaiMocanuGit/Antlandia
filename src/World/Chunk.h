#pragma once
#include <cassert>
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
    ptrdiff_t index;
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

    SpecializedVector<SpecializedVectorIndexPair<T>> objects{INIT_ADD_CHUNK, INIT_REMOVE_CHUNK, INIT_FINALISE_CHUNK, SWAP_CHUNK, DESTRUCT_CHUNK};


    Chunk() = default;
    Chunk(sf::Vector2i index, SpecializedVector<T> *ptrWorldObjects);
    Chunk(int x, int y, SpecializedVector<T> *ptrWorldObjects);


    static void INIT_ADD_CHUNK(SpecializedVectorIndexPair<T> & elem, ptrdiff_t indexChunk);
    static void INIT_REMOVE_CHUNK(SpecializedVectorIndexPair<T> & elem, ptrdiff_t indexChunk);
    static void INIT_FINALISE_CHUNK(SpecializedVectorIndexPair<T> & elem, ptrdiff_t indexChunk);
    static void SWAP_CHUNK(SpecializedVectorIndexPair<T> & elem1, ptrdiff_t atIndex1,
                           SpecializedVectorIndexPair<T> & elem2, ptrdiff_t atIndex2);

    static void DESTRUCT_CHUNK(SpecializedVectorIndexPair<T> & elem, ptrdiff_t indexChunk);



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


template <class T>
void Chunk<T>::INIT_ADD_CHUNK(SpecializedVectorIndexPair<T> &elem, ptrdiff_t indexChunk)
{
    WorldKnowledge<T> &r_knowledge = elem.ptrWorldObjects->at(elem.index).knowledge();
    assert(not r_knowledge.willAppearInNewChunk());
    r_knowledge.giveIndexInNextChunk(indexChunk);
}
template <class T>
void Chunk<T>::INIT_REMOVE_CHUNK(SpecializedVectorIndexPair<T> &elem, ptrdiff_t indexChunk)
{

}
template <typename T>
void Chunk<T>::INIT_FINALISE_CHUNK(SpecializedVectorIndexPair<T> &elem, ptrdiff_t indexChunk)
{
    WorldKnowledge<T> &r_knowledge = elem.ptrWorldObjects->at(elem.index).knowledge();
    r_knowledge.updateHomeChunkWithNext();
    r_knowledge.giveIndexInHomeChunk(indexChunk);
    r_knowledge.removeNextChunkInfo();
}

template <typename T>
void Chunk<T>::SWAP_CHUNK(SpecializedVectorIndexPair<T> &elem1, ptrdiff_t atIndex1,
                          SpecializedVectorIndexPair<T> &elem2, ptrdiff_t atIndex2)
{
    //swapping only the index as the reference to the world objects will be the same
    std::swap(elem1, elem2);
    WorldKnowledge<T> &r_knowledge1 = elem1.ptrWorldObjects->at(elem1.index).knowledge();
    WorldKnowledge<T> &r_knowledge2 = elem2.ptrWorldObjects->at(elem2.index).knowledge();

    assert(r_knowledge1.homeChunkIndexes() == r_knowledge2.homeChunkIndexes());
    r_knowledge1.giveIndexInHomeChunk(atIndex1);
    r_knowledge2.giveIndexInHomeChunk(atIndex2);
}

template <class T>
void Chunk<T>::DESTRUCT_CHUNK(SpecializedVectorIndexPair<T> &elem, ptrdiff_t indexChunk)
{
    WorldKnowledge<T> &r_knowledge = elem.ptrWorldObjects->at(elem.index).knowledge();
    r_knowledge.removeHomeChunkInfo();
}
