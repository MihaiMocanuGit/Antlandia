#pragma once
#include "Body.h"
class Ant
{
private:
    Body m_body = {};

public:
    Ant() = default;
    explicit Ant(Body body);

    const Body& body() const;
    Body& body();


};
