# Add library cpp files
add_library(json_maker INTERFACE)
target_sources(json_maker INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/json-maker/json-maker.c
)

# Add include directory
target_include_directories(json_maker INTERFACE ${CMAKE_CURRENT_LIST_DIR}/json-maker/)

# Add the standard library to the build
target_link_libraries(json_maker INTERFACE pico_stdlib)