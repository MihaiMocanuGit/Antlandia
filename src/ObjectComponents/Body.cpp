#include "Body.h"
#include <stdexcept>


Body::Body(const sf::Vector2f &pos, float size, float mass, const sf::Color &color)
    : m_position{pos}, m_size{size}, m_mass{mass}, m_color{color}
{

}


const sf::Vector2f &Body::getPosition() const
{
    return m_position;
}

void Body::setPosition(const sf::Vector2f &position)
{
    m_position = position;
}

float Body::getSize() const
{
    return m_size;
}

void Body::setSize(float size)
{
    if (size >= 0)
        m_size = size;
    else
        throw std::invalid_argument("Size must be non-negative");
}

float Body::getMass() const
{
    return m_mass;
}

void Body::setMass(float mass)
{
    if (mass >= 0)
        m_mass = mass;
    else
        throw std::invalid_argument("Mass must be non-negative");
}

const sf::Color &Body::getColor() const
{
    return m_color;
}

void Body::setColor(const sf::Color &color)
{
    m_color = color;
}

