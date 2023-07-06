#pragma once

#include <vector>
#include <functional>

#include "Ant.h"

class Chunk
{
private:
    RefVector_t<Ant> m_ants;
    sf::Vector2i m_index;

    /// \brief
    /// UpperLeft   UpperMid    UpperRight\n
    /// Left        Itself       Right\n
    /// LowerLeft   LowerMid     LowerRight
    Chunk *m_neighbours[3][3] = {{}};
public:
    static const sf::Vector2i CHUNK_SIZE;
    /// \brief Removes the ant and updates the iterator of the other ants (they remain valid)
    /// \param it - The iterator pointing to the ant to be removed;
    void removeAnt(const RefVector_t<Ant>::iterator &it);
    void addAnt(Ant& ant);

};


