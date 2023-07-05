#pragma once
#include <SFML/System/Vector2.hpp>

class WorldKnowledge
{
private:
    sf::Vector2i m_chunk = {-1, -1};
public:
    WorldKnowledge() = default;
    WorldKnowledge(int x, int y);
};
