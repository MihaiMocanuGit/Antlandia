#include "PheromoneTypes.h"



PheromoneTypes::PheromoneTypes(World *pWorld, SpecializedVector<Pheromone> *pWorldVector,
                               PrimitiveChunkMap_t<Pheromone> *pPrimitiveChunkMap)
                               : KNOWLEDGE{pWorld, pWorldVector, pPrimitiveChunkMap}
{

}
