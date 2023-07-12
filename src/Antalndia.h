#pragma once
#include "GenericObject.h"
#include "ChunkMap.h"
#include "AppLogic.h"

void startApp()
{
    World world(10, 10);

    startGameLoop(world);
}
//#include "objects/GenericObject.h"
