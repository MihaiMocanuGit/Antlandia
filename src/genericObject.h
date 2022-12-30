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
    explicit GenericObject(sf::CircleShape &aShape, sf::Vector2f aVelocity = {0, 0});

    GenericObject(const GenericObject &object);
    friend void swap(GenericObject &first, GenericObject &second);

    GenericObject& operator=(GenericObject other);
    GenericObject(GenericObject&& other) noexcept;
    ~GenericObject();

    template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
    void moveTo(World<MAP_SIZE_X, MAP_SIZE_Y> &rWorld, sf::Vector2f position)
    {
        rWorld.antController.moveObjectAtIndexTo(m_indexInHolder, position);
    }

    template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y>
    void moveBy(World<MAP_SIZE_X, MAP_SIZE_Y> &rWorld, sf::Vector2f offset)
    {
        rWorld.antController.moveObjectAtIndexBy(m_indexInHolder, offset);
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
