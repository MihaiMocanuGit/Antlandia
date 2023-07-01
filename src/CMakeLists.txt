add_subdirectory(objects)
add_library(src AntLogic.h)
target_link_libraries(src objects)