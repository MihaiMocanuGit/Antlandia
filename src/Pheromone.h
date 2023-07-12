#pragma once
#include "GenericObject.h"

class Pheromone
{
private:
    GenericObject m_genericObject = {};

public:
    Pheromone() = default;
    explicit Pheromone(GenericObject genericObject);

    GenericObject& genericObject();
    const GenericObject& genericObject() const;
};



