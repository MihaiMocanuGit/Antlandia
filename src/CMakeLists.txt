#add_subdirectory(objects)
add_library(src Antalndia.h
        Body.cpp Body.h
        Ant.cpp Ant.h WordKnowledge.cpp WorldKnowledge.h Chunk.cpp Chunk.h Types.h)
#target_link_libraries(src objects)