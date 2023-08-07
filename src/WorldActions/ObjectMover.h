#pragma once
#include "../World/World.h"

template <class T>
class ObjectMover
{
private:
    World &m_ref_world;

    /// \brief Moves the given object from its homeChunk into another chunk.
    /// \n
    /// The object is not physically moved, it's only removed from the home chunk vector and
    /// it is then inserted into another chunk's vector, changing
    /// \param object The object whose home chunk we want to be changed
    /// \param newChunk The indexes of the new chunk in the ChunkMap
    /// \return the index of the GenericObject in the new chunk vector
    ptrdiff_t m_moveIntoChunk(GenericObject<T> &object, const sf::Vector2i &newChunk);

public:
    explicit ObjectMover(World &ref_world);

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

    if (not m_ref_world.map().spotsAreInSameChunk(oldPosition, newPosition))
    {
        sf::Vector2i newChunkIndex = m_ref_world.map().computeChunkIndex(newPosition);
        m_moveIntoChunk(object, newChunkIndex);
    }

    object.body().setPosition(newPosition);
}


template <class T>
ptrdiff_t ObjectMover<T>::m_moveIntoChunk(GenericObject<T> &object, const sf::Vector2i &newChunk)
{
    //getting the needed data
    WorldKnowledge<T> &r_knowledge = object.knowledge();
    sf::Vector2i homeChunkXY = r_knowledge.oldChunkIndex();
    size_t oldChunkIndex = xyToIndex(homeChunkXY.x, homeChunkXY.y, m_ref_world.size().x);
    Chunk<T> &r_oldChunk = r_knowledge.primitiveChunkMap().at(oldChunkIndex);

    //marking the object to be removed from the old chunk
    //we also make a debug assert that the object does physically exist in its home chunk
    ptrdiff_t indexInOldChunk = r_knowledge.indexInChunk();
    assert(indexInOldChunk >= 0);
    r_oldChunk.objects.toBeRemoved((size_t)indexInOldChunk);


    //marking the object to be added in the new chunk
    size_t newChunkIndex = xyToIndex(newChunk.x, newChunk.y, m_ref_world.size().x);
    Chunk<T> &r_newChunk = r_knowledge.primitiveChunkMap().at(newChunkIndex);
    SpecializedVectorIndexPair<T> pairElement = {r_knowledge.pWorldObjectVector(), r_knowledge.indexInWorld()};
    r_newChunk.objects.toBeAdded(std::move(pairElement));
}

template <class T>
ObjectMover<T>::ObjectMover(World &ref_world) : m_ref_world{ref_world}
{

}
