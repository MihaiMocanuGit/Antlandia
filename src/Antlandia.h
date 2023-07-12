#pragma once
#include "GenericObject.h"
#include "ChunkMap.h"
#include "AppLogic.h"

void startApp()
{
    World world(10, 10);

    for (int i = 0; i < 125; ++i)
        world.addAnt(sf::Vector2f(i*5.0f, i*5.0f));


    world.ants().addAll();
    startGameLoop(world);
}
//#include "objects/GenericObject.h"
