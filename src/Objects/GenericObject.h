#pragma once
#include "../ObjectComponents/Body.h"
#include "../ObjectComponents/WorldKnowledge.h"

template <class T>
class GenericObject
{
private:
    Body m_body = {};
    WorldKnowledge<T> m_worldKnowledge = {};
public:
    GenericObject() = default;
    GenericObject(Body body, WorldKnowledge<T> worldKnowledge);

    Body &body();
    const Body &body() const;

    WorldKnowledge<T> &knowledge();
    const WorldKnowledge<T> &knowledge() const;
};

template <class T>
const WorldKnowledge<T> &GenericObject<T>::knowledge() const
{
    return m_worldKnowledge;
}

template <class T>
WorldKnowledge<T> &GenericObject<T>::knowledge()
{
    return m_worldKnowledge;
}

template <class T>
const Body &GenericObject<T>::body() const
{
    return m_body;
}

template <class T>
Body &GenericObject<T>::body()
{
    return m_body;
}

template <class T>
GenericObject<T>::GenericObject(Body body, WorldKnowledge<T> worldKnowledge)
        : m_body{std::move(body)}, m_worldKnowledge{std::move(worldKnowledge)}
{

}
