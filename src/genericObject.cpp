#include "genericObject.h"
#include <iostream>

int contor = 0;
void GenericObject::m_initPtrShape(DEBBUG_TYPE &object)
{
    std::cout << pShape << '\t';
    pShape =  new DEBBUG_TYPE;
    std::cout << pShape << '\n';

    *pShape = object;
}


void GenericObject::m_initPtrShape()
{
    std::cout << pShape << '\t';
    pShape =  new DEBBUG_TYPE;
    std::cout << pShape << '\n';

    //for debugging 
    //pShape->setFillColor(sf::Color::Magenta);
    //pShape->setRadius(5);


}

GenericObject::GenericObject()
{
    m_initPtrShape();
}

GenericObject::GenericObject(DEBBUG_TYPE &aShape) 
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

