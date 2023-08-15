#pragma once

#include "../ObjectComponents/Body.h"
#include "../ObjectComponents/WorldKnowledge.h"
#include "GenericObject.h"

/// \brief This is an example used to represent the base structure and functionality of every Object
class TemplateForObject
{
private:
    GenericObject<TemplateForObject> m_genericObject;
public:
    TemplateForObject() = default;
    explicit TemplateForObject(GenericObject<TemplateForObject> genericObject);
    TemplateForObject(Body body, WorldKnowledge<TemplateForObject> worldKnowledge);

    Body &body();
    const Body &body() const;

    WorldKnowledge<TemplateForObject> &knowledge();
    const WorldKnowledge<TemplateForObject> &knowledge() const;

    GenericObject<TemplateForObject> &genericObject();
    const GenericObject<TemplateForObject> &genericObject() const;
};

