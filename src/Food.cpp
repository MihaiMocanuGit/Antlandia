#include "Food.h"

Food::Food(Body body, WorldKnowledge worldKnowledge) : m_body{std::move(body)}, m_worldKnowledge{std::move(worldKnowledge)}
{

}

Body &Food::body()
{
    return m_body;
}

const Body &Food::body() const
{
    return m_body;
}

WorldKnowledge &Food::knowledge()
{
    return m_worldKnowledge;
}

const WorldKnowledge &Food::knowledge() const
{
    return m_worldKnowledge;
}
