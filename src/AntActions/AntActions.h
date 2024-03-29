#pragma once
#include "../Objects/Ant.h"
#include "../World/World.h"

namespace AntActions
{

void searchFood(Ant &r_ant, World &r_world, unsigned currentFrame);
void grabFood(Ant &r_ant, World &r_world, unsigned currentFrame);
void bringFood(Ant &r_ant, World &r_world, unsigned currentFrame);

} //end AntActions namespace