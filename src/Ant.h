#pragma once
#include "GenericObject.h"
class Ant
{
private:
    GenericObject m_genericObject = {};

public:
    Ant() = default;
    GenericObject& genericObject();
    const GenericObject& genericObject() const;
};

