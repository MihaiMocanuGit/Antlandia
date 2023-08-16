#pragma once
#include "../Objects/Pheromone.h"


class PheromoneTypes
{
private:

public:
    PheromoneTypes(World *pWorld, SpecializedVector<Pheromone> *pWorldVector, PrimitiveChunkMap_t<Pheromone> *pPrimitiveChunkMap);
    const WorldKnowledge<Pheromone> KNOWLEDGE;

    const Body TRAIL_PHEROMONE_BODY = {sf::Vector2f{-1.0f, -1.0f}, 1.0f, 1.0f,
                                       sf::Vector3<unsigned char>{0, 255, 0}};
    const Pheromone TRAIL_PHEROMONE = {TRAIL_PHEROMONE_BODY, KNOWLEDGE, Pheromone::Type_e::Trail};

    const Body FOOD_PHEROMONE_BODY = {sf::Vector2f{-1.0f, -1.0f}, 1.5f, 1.0f,
                                      sf::Vector3<unsigned char>{255, 255, 0}};
    const Pheromone FOOD_PHEROMONE = {FOOD_PHEROMONE_BODY, KNOWLEDGE, Pheromone::Type_e::Food};


    const Body HOME_PHEROMONE_BODY = {sf::Vector2f{-1.0f, -1.0f}, 1.0f, 10.0f,
                                      sf::Vector3<unsigned char>{0, 255, 255}};
    const Pheromone HOME_PHEROMONE = {HOME_PHEROMONE_BODY, KNOWLEDGE, Pheromone::Type_e::Home};
};