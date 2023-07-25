#add_subdirectory(objects)
add_library(src Antlandia.h
        Body.cpp Body.h
        WordKnowledge.cpp WorldKnowledge.h
        Chunk.cpp Chunk.h
        Types.h
        SpecializedVector.h
        Ant.cpp Ant.h
        Pheromone.cpp Pheromone.h
        Food.cpp Food.h
        ChunkMap.cpp ChunkMap.h
        AppLogic.h World.cpp World.h AppLogic.cpp AppLogic.cpp AppLogic.h Antlandia.cpp)
#target_link_libraries(src objects)