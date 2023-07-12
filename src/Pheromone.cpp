#include "Pheromone.h"

GenericObject &Pheromone::genericObject()
{
    return m_genericObject;
}

const GenericObject &Pheromone::genericObject() const
{
    return m_genericObject;
}

Pheromone::Pheromone(GenericObject genericObject) : m_genericObject{std::move(genericObject)}
{

}
