#pragma once
#include "../Objects/Ant.h"


class AntTypes
{
private:

public:
    AntTypes(World *pWorld, SpecializedVector<Ant> *pWorldVector, PrimitiveChunkMap_t<Ant> *pPrimitiveChunkMap);
    const WorldKnowledge<Ant> KNOWLEDGE;

    const Body WORKER_ANT_BODY = {sf::Vector2f{-1.0f, -1.0f}, 2.0f, 1.0f,
                                       sf::Vector3<unsigned char>{0, 0, 0}};
    const Ant WORKER_ANT = {WORKER_ANT_BODY, KNOWLEDGE, Ant::Type_e::Worker};

    const Body MALE_ANT_BODY = {sf::Vector2f{-1.0f, -1.0f}, 1.5f, 1.0f,
                                  sf::Vector3<unsigned char>{50, 0, 150}};
    const Ant MALE_ANT = {MALE_ANT_BODY, KNOWLEDGE, Ant::Type_e::Male};

    const Body QUEEN_ANT_BODY = {sf::Vector2f{-1.0f, -1.0f}, 4.0f, 4.0f,
                                  sf::Vector3<unsigned char>{150, 0, 50}};
    const Ant QUEEN_ANT = {QUEEN_ANT_BODY, KNOWLEDGE, Ant::Type_e::Queen};


};