#include "Ant.h"

GenericObject &Ant::genericObject()
{
    return m_genericObject;
}

const GenericObject &Ant::genericObject() const
{
    return m_genericObject;
}

Ant::Ant(GenericObject genericObject) : m_genericObject{std::move(genericObject)}
{

}
