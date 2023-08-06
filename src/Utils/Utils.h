#pragma once
#include <SFML/Graphics.hpp>

#include "../ObjectComponents/Body.h"

sf::CircleShape getShape(const Body &body);

size_t xyToIndex(int x, int y, unsigned sizeX);