#pragma once
#include "GenericObject.h"


class Food
{
private:
    GenericObject m_genericObject = {};

public:
    Food() = default;
    explicit Food(GenericObject genericObject);

    GenericObject& genericObject();
    const GenericObject& genericObject() const;
};



