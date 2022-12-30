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
    //used when initing a genericObject created with no parameters
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
    this->m_indexInHolder = object.m_indexInHolder;

    this->m_initPtrShape(*object.m_pShape);
    this->m_velocity = object.m_velocity;
}

void swap(GenericObject &first, GenericObject &second)
{
    ///https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
    // enable ADL (not necessary in our case, but good practice)
    using std::swap;

    // by swapping the members of two objects,
    // the two objects are effectively swapped
    swap(first.m_pHomeChunk, second.m_pHomeChunk);
    swap(first.m_indexInHolder, second.m_indexInHolder);
    swap(first.m_pShape, second.m_pShape);
    swap(first.m_velocity, second.m_velocity);
}

GenericObject& GenericObject::operator = (GenericObject other)
{
    swap(*this, other);

    return *this;

}

GenericObject::GenericObject(GenericObject&& other) noexcept
{
    swap(*this, other);
}

GenericObject& GenericObject::operator=(GenericObject&& other) noexcept
{

    if (this != &other)
    {
        // Free the existing resource.
        delete m_pShape;

        swap(*this, other);
        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        other.m_pShape = nullptr;
        other.m_pHomeChunk = nullptr;
    }
    return *this;
}


GenericObject::~GenericObject()
{
    //std::cout << '-' << pShape << '\t';
    
    delete m_pShape;
    m_pShape = nullptr;
    //std::cout << '-' << pShape << '\n';  
}


const Chunk *GenericObject::getPtrHomeChunk() const
{
    return m_pHomeChunk;
}

void GenericObject::setPtrHomeChunk(Chunk *pHomeChunk)
{
    m_pHomeChunk = pHomeChunk;
}
const unsigned int GenericObject::getIndexInHolder() const
{
    return m_indexInHolder;
}
void GenericObject::setIndexInHolder(unsigned int indexInHolder)
{
    m_indexInHolder = indexInHolder;
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