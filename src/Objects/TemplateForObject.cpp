#include "TemplateForObject.h"

TemplateForObject::TemplateForObject(Body body, WorldKnowledge<TemplateForObject> worldKnowledge) : TemplateForObject(GenericObject<TemplateForObject>{std::move(body), std::move(worldKnowledge)})
{

}

Body &TemplateForObject::body()
{
    return genericObject().body();
}

const Body &TemplateForObject::body() const
{
    return genericObject().body();
}

WorldKnowledge<TemplateForObject> &TemplateForObject::knowledge()
{
    return genericObject().knowledge();
}

const WorldKnowledge<TemplateForObject> &TemplateForObject::knowledge() const
{
    return genericObject().knowledge();
}

TemplateForObject::TemplateForObject(GenericObject<TemplateForObject> genericObject) : m_genericObject{std::move(genericObject)}
{

}

GenericObject<TemplateForObject> &TemplateForObject::genericObject()
{
    return m_genericObject;
}

const GenericObject<TemplateForObject> &TemplateForObject::genericObject() const
{
    return m_genericObject;
}
