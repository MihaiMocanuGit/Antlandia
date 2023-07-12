#pragma once
#include "Chunk.h"

class ChunkMap
{
private:
    //we will consider it to be a matrix
    std::vector<Chunk> m_chunkMap = {};
    sf::Vector2u m_size = {0, 0};

    [[nodiscard]] inline bool m_isValidIndex(unsigned x, unsigned y) const;
    void m_initChunks();
public:
    ChunkMap() = default;
    explicit ChunkMap(sf::Vector2u size);
    ChunkMap(unsigned sizeX, unsigned sizeY);

    Chunk& at(sf::Vector2u index);
    Chunk& at(unsigned int x, unsigned int y);

    [[nodiscard]] sf::Vector2u size() const;
};
