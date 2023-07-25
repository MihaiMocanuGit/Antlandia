#pragma once
#include <SFML/Graphics.hpp>

#include "World.h"


sf::CircleShape getShape(const Body &body);
void startGameLoop(World& world);

