#include "genericObject.h"
#include <iostream>

int contor = 0;
sf::CircleShape *GenericObject::m_initPtrShape(sf::CircleShape object)
{
   
    sf::CircleShape *pObject = new sf::CircleShape();
    *pObject = object;

    return pObject;
}

GenericObject::GenericObject()
{

}

GenericObject::GenericObject(sf::CircleShape aShape) 
{
    pShape = m_initPtrShape(aShape);
}

GenericObject::~GenericObject()
{
    std::cout << pShape << '\t';
    if(pShape == nullptr)
    delete pShape;
}

