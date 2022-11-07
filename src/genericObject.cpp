#include "genericObject.h"
#include <iostream>

int contor = 0;
void GenericObject::m_initPtrShape(sf::CircleShape &object)
{
    //std::cout << pShape << '\t';
    m_pShape =  new sf::CircleShape;
    //std::cout << pShape << '\n';

    *m_pShape = object;
}


void GenericObject::m_initPtrShape()
{
    //std::cout << pShape << '\t';
    m_pShape =  new sf::CircleShape;
    //std::cout << pShape << '\n';

    //for debugging 
    m_pShape->setFillColor(sf::Color::Magenta);
    m_pShape->setRadius(5);


}

GenericObject::GenericObject()
{
    m_initPtrShape();
}

GenericObject::GenericObject(sf::CircleShape &aShape, sf::Vector2f aVelocity) 
{

    m_initPtrShape(aShape);
    m_velocity = aVelocity;
}

GenericObject::GenericObject(const GenericObject &object) 
{
    this->m_pHomeChunk = object.m_pHomeChunk;


    this->m_initPtrShape(*object.m_pShape);

}


GenericObject::~GenericObject()
{
    //std::cout << '-' << pShape << '\t';
    
    delete m_pShape;
    m_pShape = nullptr;
    //std::cout << '-' << pShape << '\n';  
}

void GenericObject::moveTo(sf::Vector2f position)
{
    m_pShape->setPosition(position);
}

void GenericObject::moveBy(sf::Vector2f offset)
{
    sf::Vector2f currentPosition = m_pShape->getPosition();
    m_pShape->setPosition(currentPosition + offset);
}

void GenericObject::setPtrHomeChunk(void *pHomeChunk)
{
    m_pHomeChunk = pHomeChunk;
}

const sf::Vector2f &GenericObject::getPosition() const
{
    return m_pShape->getPosition();
}

void GenericObject::setPosition(sf::Vector2f position)
{
    m_pShape->setPosition(position);
}

const sf::CircleShape &GenericObject::getShape() const
{
     return *m_pShape;
}