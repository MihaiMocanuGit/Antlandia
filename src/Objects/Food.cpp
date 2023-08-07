#include "Food.h"


Food::Food(Body body, WorldKnowledge<Food> worldKnowledge)
    : Food(GenericObject<Food>{std::move(body),std::move(worldKnowledge)})
{

}

Body &Food::body()
{
    return m_genericObject.body();
}

const Body &Food::body() const
{
    return m_genericObject.body();
}

WorldKnowledge<Food> &Food::knowledge()
{
    return m_genericObject.knowledge();
}

const WorldKnowledge<Food> &Food::knowledge() const
{
    return m_genericObject.knowledge();
}

Food::Food(GenericObject <Food> genericObject) : m_genericObject{std::move(genericObject)}
{

}

GenericObject<Food> &Food::genericObject()
{
    return m_genericObject;
}

const GenericObject<Food> &Food::genericObject() const
{
    return m_genericObject;
}
