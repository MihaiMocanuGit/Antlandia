#pragma once


template <class T>
using SwapFct_t = void (*)(T&, ptrdiff_t , T&, ptrdiff_t);
template <class T>
using InitToBeAddedFct_t = void (*)(T&, ptrdiff_t);
template <class T>
using InitToBeRemovedFct_t = void (*)(T&, ptrdiff_t);
template <class T>
using InitForFinaliseFct_t = void (*)(T&, ptrdiff_t);

template <class T>
using DestructFct_t = void (*)(T&, ptrdiff_t);

template <typename T>
class Chunk;
//we will consider it to be a matrix
template <typename T>
using PrimitiveChunkMap_t = std::vector<Chunk<T>>;