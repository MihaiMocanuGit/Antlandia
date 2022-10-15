#include "genericObject.h"
#include <iostream>

int contor = 0;
void GenericObject::m_initPtrShape(sf::CircleShape &object)
{
    std::cout << pShape << '\t';
    pShape =  new sf::CircleShape;
    std::cout << pShape << '\n';

    *pShape = object;
}


void GenericObject::m_initPtrShape()
{
    std::cout << pShape << '\t';
    pShape =  new sf::CircleShape;
    std::cout << pShape << '\n';

    //for debugging 
    //pShape->setFillColor(sf::Color::Magenta);
    //pShape->setRadius(5);


}

GenericObject::GenericObject()
{
    m_initPtrShape();
}

GenericObject::GenericObject(sf::CircleShape &aShape) 
{

    m_initPtrShape(aShape);
}

GenericObject::~GenericObject()
{
    std::cout << '-' << pShape << '\t';
    
    delete pShape;
    pShape = nullptr;
    std::cout << '-' << pShape << '\n';  
}

