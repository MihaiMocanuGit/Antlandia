#ifndef GENERIC_OBJECT_H
#define GENERIC_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/*
 * Forward Declarations of classes due to circular dependencies
 */
class Chunk;
template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
class World;


class GenericObject
{
private:

    void m_initPtrShape(sf::CircleShape &object);
    void m_initPtrShape();

protected:
    Chunk *m_pHomeChunk = nullptr;
    unsigned int m_indexInHolder;

    sf::CircleShape *m_pShape = nullptr;
    sf::Vector2f m_velocity;

public:


    GenericObject();
    GenericObject(sf::CircleShape &aShape);
    GenericObject(sf::CircleShape &aShape, sf::Vector2f aVelocity);

    GenericObject(const GenericObject &object);

    ~GenericObject();

    template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
    void moveTo(World<MAP_SIZE_X, MAP_SIZE_Y> &rWorld, sf::Vector2f position)
    {
        rWorld.moveAntAtIndexTo(m_indexInHolder, position);
    }

    template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
    void moveBy(World<MAP_SIZE_X, MAP_SIZE_Y> &rWorld, sf::Vector2f offset)
    {
        rWorld.moveAntAtIndexBy(m_indexInHolder, offset);
    }

    const Chunk *getPtrHomeChunk() const;
    void setPtrHomeChunk(Chunk *pHomeChunk);

    const unsigned int getIndexInHolder() const;
    void setIndexInHolder(unsigned int indexInHolder);

    const sf::Vector2f &getPosition() const;
    void setPosition(sf::Vector2f position);

    const sf::CircleShape &getShape() const;



};

#endif
