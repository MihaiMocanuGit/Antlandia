#add_subdirectory(objects)
add_library(src Antalndia.h
        Body.cpp Body.h
        GenericObject.cpp GenericObject.h WordKnowledge.cpp WorldKnowledge.h Chunk.cpp Chunk.h Types.h ChunkContainer.cpp SpecializedVector.h Ant.cpp Ant.h Pheromone.cpp Pheromone.h Food.cpp Food.h ChunkMap.cpp ChunkMap.h ChunkMap.cpp ChunkMap.h ChunkMap.cpp ChunkMap.h ChunkMap.cpp ChunkMap.h ChunkMap.cpp ChunkMap.h ChunkMap.cpp ChunkMap.h Graphics.h)
#target_link_libraries(src objects)