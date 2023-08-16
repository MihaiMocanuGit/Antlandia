#add_subdirectory(Objects)
add_library(src
        Antlandia.h Antlandia.cpp
        AppLogic/AppLogic.cpp AppLogic/AppLogic.cpp
        ObjectComponents/Body.cpp ObjectComponents/Body.h
        ObjectComponents/WorldKnowledge.h
        World/Chunk.h
        Utils/Types.h
        Utils/SpecializedVector.h
        Objects/Ant.cpp Objects/Ant.h
        Objects/Pheromone.cpp Objects/Pheromone.h
        Objects/Food.cpp Objects/Food.h
        World/ChunkMap.cpp World/ChunkMap.h
        World/World.cpp World/World.h
        Utils/Utils.cpp Utils/Utils.h
        Objects/GenericObject.h
        WorldActions/ObjectMover.h
        WorldActions/ObjectSpawner.cpp
        WorldActions/ObjectSpawner.h
        Objects/TemplateForObject.cpp
        Objects/TemplateForObject.h
        WorldActions/ObjectMover.cpp
        ObjectTypes/PheromoneTypes.cpp
        ObjectTypes/PheromoneTypes.h
        ObjectTypes/AntTypes.cpp
        ObjectTypes/AntTypes.h)
#target_link_libraries(src Objects)