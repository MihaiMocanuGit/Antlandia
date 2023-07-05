#include <utility>
#include "Ant.h"

Ant::Ant(Body body) : m_body{std::move(body)}
{

}

const Body &Ant::body() const
{
    return m_body;
}

Body &Ant::body()
{
    return m_body;
}
