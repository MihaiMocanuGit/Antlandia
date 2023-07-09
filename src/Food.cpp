
#include "Food.h"

GenericObject &Food::genericObject()
{
    return m_genericObject;
}

const GenericObject &Food::genericObject() const
{
    return m_genericObject;
}
