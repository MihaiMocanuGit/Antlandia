#pragma once


template <class T>
using SwapFunction_t = void (*)(T&, size_t, T&, size_t);

template <class T>
using InitFunction_t = void (*)(T&, size_t);

template <typename T>
class Chunk;
//we will consider it to be a matrix
template <typename T>
using PrimitiveChunkMap_t = std::vector<Chunk<T>>;