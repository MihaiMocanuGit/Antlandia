#include "Utils.h"

sf::CircleShape getShape(const Body &body)
{
    static sf::CircleShape shape;
    float size = body.getSize();
    shape.setRadius(size);

    const sf::Color &color = body.getColor();
    shape.setFillColor(color);

    sf::Vector2f position(body.getPosition());
    shape.setPosition(position);
    return shape;
}


size_t xyToIndex(int x, int y, unsigned sizeX)
{
    return x + y * sizeX;
}
