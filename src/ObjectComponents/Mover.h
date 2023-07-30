#pragma once

#include "GenericObject.h"

class Mover
{
private:
    GenericObject &m_ref_genericBody;
public:
    explicit Mover(GenericObject &ref_genericBody);
};
