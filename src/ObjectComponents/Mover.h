#pragma once

#include "Body.h"
#include "WorldKnowledge.h"

template <class T>
class Mover
{
private:
    Body &m_ref_body;
    WorldKnowledge<T> &m_ref_worldKnowledge;
public:
    Mover(Body &ref_body, WorldKnowledge<T> & ref_worldKnowledge)
    : m_ref_body{ref_body}, m_ref_worldKnowledge{ref_worldKnowledge}
    {}
};
