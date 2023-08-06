#include "Utils.h"

sf::CircleShape getShape(const Body &body)
{
    float size = body.getSize();
    sf::CircleShape shape(size);

    const sf::Vector3<unsigned char> &color = body.getColor();
    sf::Color colorSf(color.x, color.y, color.z);
    shape.setFillColor(colorSf);

    sf::Vector2f position(body.getPosition());
    shape.setPosition(position);

    return shape;
}


size_t xyToIndex(int x, int y, unsigned sizeX)
{
    return x + y * sizeX;
}
