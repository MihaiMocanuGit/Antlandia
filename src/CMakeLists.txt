#add_subdirectory(objects)
add_library(src
        Antlandia.h Antlandia.cpp
        AppLogic.cpp AppLogic.cpp
        Body.cpp Body.h
        WordKnowledge.cpp WorldKnowledge.h
        Chunk.cpp Chunk.h
        Types.h
        SpecializedVector.h
        Ant.cpp Ant.h
        Pheromone.cpp Pheromone.h
        Food.cpp Food.h
        ChunkMap.cpp ChunkMap.h
        World.cpp World.h
        )
#target_link_libraries(src objects)