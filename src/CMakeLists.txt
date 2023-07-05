#add_subdirectory(objects)
add_library(src AntLogic.h
        Body.cpp Body.h
        Ant.cpp Ant.h)
#target_link_libraries(src objects)