#include "AntTypes.h"

AntTypes::AntTypes(World *pWorld, SpecializedVector<Ant> *pWorldVector,
                   PrimitiveChunkMap_t<Ant> *pPrimitiveChunkMap)
                   : KNOWLEDGE{pWorld, pWorldVector, pPrimitiveChunkMap}
{

}
