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

protected:
    Chunk *m_pHomeChunk = nullptr;

    template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
    ObjectOrganizer<MAP_SIZE_X, MAP_SIZE_Y> *m_pObjOrganizer = nullptr;

    sf::CircleShape *m_pShape = nullptr;
    sf::Vector2f m_velocity;

public:


    GenericObject();
    GenericObject(sf::CircleShape &aShape);
    GenericObject(sf::CircleShape &aShape, sf::Vector2f aVelocity);

    GenericObject(const GenericObject &object);

    ~GenericObject();

    void moveTo(sf::Vector2f position);
    void moveBy(sf::Vector2f offset);

    const Chunk *getPtrHomeChunk() const;
    void setPtrHomeChunk(Chunk *pHomeChunk);

    //const ObjectOrganizer

    const sf::Vector2f &getPosition() const;
    void setPosition(sf::Vector2f position);

    const sf::CircleShape &getShape() const;



};

#endif
