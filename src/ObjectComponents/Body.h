#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
class Body
{
private:
    sf::Vector2f m_position {-1.0f, -1.0f};
    float m_size = -1;
    float m_mass = -1;
    sf::Color m_color = {0, 0, 0, 255};
public:
    Body() = default;
    Body(const sf::Vector2f &pos, float size, float mass, const sf::Color &color);

    [[nodiscard]] const sf::Vector2f &getPosition() const;

    void setPosition(const sf::Vector2f &position);

    [[nodiscard]] float getSize() const;

    void setSize(float size);

    [[nodiscard]] float getMass() const;

    void setMass(float mass);

    [[nodiscard]] const sf::Color &getColor() const;

    void setColor(const sf::Color &color);

};


