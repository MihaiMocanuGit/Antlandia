#ifndef GENERIC_OBJECT_H
#define GENERIC_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/*
 * Forward Declarations of classes due to circular dependencies
 */
class Chunk;
template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
class ObjectOrganizer;


class GenericObject
{
private:

    void m_initPtrShape(sf::CircleShape &object);
    void m_initPtrShape();

    unsigned int m_indexInWorld;
protected:
    Chunk *m_pHomeChunk = nullptr;

    sf::CircleShape *m_pShape = nullptr;
    sf::Vector2f m_velocity;

public:


    GenericObject();
    GenericObject(sf::CircleShape &aShape);
    GenericObject(sf::CircleShape &aShape, sf::Vector2f aVelocity);

    GenericObject(const GenericObject &object);

    ~GenericObject();

    template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
    void moveTo(ObjectOrganizer<MAP_SIZE_X, MAP_SIZE_Y> &world, sf::Vector2f position)
    {
        world.moveAntAtIndexTo(m_indexInWorld, position);
    }

    template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
    void moveBy(ObjectOrganizer<MAP_SIZE_X, MAP_SIZE_Y> &world, sf::Vector2f offset)
    {
        world.moveAntAtIndexBy(m_indexInWorld, offset);
    }

    const Chunk *getPtrHomeChunk() const;
    void setPtrHomeChunk(Chunk *pHomeChunk);

    //const ObjectOrganizer

    const sf::Vector2f &getPosition() const;
    void setPosition(sf::Vector2f position);

    const sf::CircleShape &getShape() const;



};

#endif
