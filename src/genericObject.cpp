#include "genericObject.h"
#include <iostream>

int contor = 0;
void GenericObject::m_initPtrShape(sf::CircleShape &object)
{
    //std::cout << pShape << '\t';
    pShape =  new sf::CircleShape;
    //std::cout << pShape << '\n';

    *pShape = object;
}


void GenericObject::m_initPtrShape()
{
    //std::cout << pShape << '\t';
    pShape =  new sf::CircleShape;
    //std::cout << pShape << '\n';

    //for debugging 
    pShape->setFillColor(sf::Color::Magenta);
    pShape->setRadius(5);


}

GenericObject::GenericObject()
{
    m_initPtrShape();
}

GenericObject::GenericObject(sf::CircleShape &aShape, sf::Vector2f aVelocity) 
{

    m_initPtrShape(aShape);
    velocity = aVelocity;
}

GenericObject::GenericObject(const GenericObject &object) 
{
    this->m_pHomeChunk = object.m_pHomeChunk;


    this->m_initPtrShape(*object.pShape);

}


GenericObject::~GenericObject()
{
    //std::cout << '-' << pShape << '\t';
    
    delete pShape;
    pShape = nullptr;
    //std::cout << '-' << pShape << '\n';  
}

void GenericObject::moveTo(sf::Vector2f position)
{
    pShape->setPosition(position);
}

void GenericObject::moveBy(sf::Vector2f offset)
{
    sf::Vector2f currentPosition = pShape->getPosition();
    pShape->setPosition(currentPosition + offset);
}

void GenericObject::setPtrHomeChunk(void *pHomeChunk)
{
    m_pHomeChunk = pHomeChunk;
}