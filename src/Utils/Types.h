#pragma once




template <typename T>
class Chunk;
//we will consider it to be a matrix
template <typename T>
using PrimitiveChunkMap_t = std::vector<Chunk<T>>;

struct CornerBounds
{
    sf::Vector2i upperLeft, lowerRight;
};