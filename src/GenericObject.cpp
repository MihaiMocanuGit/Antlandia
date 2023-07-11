#include <utility>
#include "GenericObject.h"

GenericObject::GenericObject(Body body, WorldKnowledge<GenericObject> knowledge) : m_body{std::move(body)}, m_knowledge{std::move(knowledge)}
{

}

const Body &GenericObject::body() const
{
    return m_body;
}

Body &GenericObject::body()
{
    return m_body;
}

void GenericObject::insertWorldKnowledge(const WorldKnowledge &knowledge)
{
    m_knowledge = knowledge;
}

const WorldKnowledge &GenericObject::knowledge() const
{
    return m_knowledge;
}

WorldKnowledge &GenericObject::knowledge()
{
    return m_knowledge;
}
