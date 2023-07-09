#pragma once

#include <vector>
#include <functional>

#include "GenericObject.h"
#include "Ant.h"
#include "ChunkContainer.h"
class Chunk
{
    friend class ChunkMap;
private:
    ChunkContainer m_ants;
    sf::Vector2i m_index;

    /// \brief
    /// UpperLeft   UpperMid    UpperRight\n
    /// Left        Itself       Right\n
    /// LowerLeft   LowerMid     LowerRight
    Chunk *m_neighbours[3][3] = {{}};
public:
    static const sf::Vector2i CHUNK_SIZE;
    /// \brief Removes the ant and updates the indexes of the other ants (they remain valid)
    /// \param index - The index of the ant to be removed;
    void removeAnt(size_t index);
    void addAnt(Ant& ant);

};


