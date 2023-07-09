#pragma once
#include "GenericObject.h"


class Food
{
private:
    GenericObject m_genericObject = {};

public:
    Food() = default;
    GenericObject& genericObject();
    const GenericObject& genericObject() const;
};



