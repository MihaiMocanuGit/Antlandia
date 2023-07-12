#pragma once
#include "GenericObject.h"
#include "ChunkMap.h"
#include "AppLogic.h"

void startApp()
{
    World world(10, 10);

    for (int i = 0; i < 100; ++i)
    {
        Body body(sf::Vector2f(i*5.0f, i*5.0f), 1, 1, sf::Vector3<unsigned char>{0, 0, 0});
        Ant ant = world.createObject<Ant>(body);
        world.ants().toBeAdded(ant);
    }

    world.ants().addAll();
    startGameLoop(world);
}
//#include "objects/GenericObject.h"
