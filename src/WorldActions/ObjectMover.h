#pragma once
#include "../World/ChunkMap.h"

#include <cassert>

template <class T>
class ObjectMover
{
private:
    ChunkMap &m_r_chunkMap;

    /// \brief Moves the given object from its homeChunk into another chunk.
    /// \n
    /// The object is not physically moved, it's only removed from the home chunk vector and
    /// it is then inserted into another chunk's vector, changing
    /// \param object The object whose home chunk we want to be changed
    /// \param newChunk The indexes of the new chunk in the ChunkMap
    /// \return the index of the GenericObject in the new chunk vector
    ptrdiff_t m_moveIntoChunk(GenericObject<T> &object, const sf::Vector2i &newChunk);

public:
    explicit ObjectMover(ChunkMap &r_chunkMap);

    void moveTo(GenericObject<T> &object, const sf::Vector2f &newPosition);
    void moveBy(GenericObject<T> &object, const sf::Vector2f &newPosition);
};

template <class T>
void ObjectMover<T>::moveBy(GenericObject<T> &object, const sf::Vector2f &newPosition)
{
    moveTo(object, object.body().getPosition() + newPosition);
}

template <class T>
void ObjectMover<T>::moveTo(GenericObject<T> &object, const sf::Vector2f &newPosition)
{
    sf::Vector2f oldPosition = object.body().getPosition();
    //TODO: Assert that the new position is valid
    // If not, maybe clamp the position inside world borders?

    if (not m_r_chunkMap.spotsAreInSameChunk(oldPosition, newPosition))
    {
        sf::Vector2i newChunkIndex = m_r_chunkMap.computeChunkIndex(newPosition);
        m_moveIntoChunk(object, newChunkIndex);
    }

    object.body().setPosition(newPosition);
}


template <class T>
ptrdiff_t ObjectMover<T>::m_moveIntoChunk(GenericObject<T> &object, const sf::Vector2i &newChunk)
{
    return -1;
}

template <class T>
ObjectMover<T>::ObjectMover(ChunkMap &r_chunkMap) : m_r_chunkMap{r_chunkMap}
{

}
