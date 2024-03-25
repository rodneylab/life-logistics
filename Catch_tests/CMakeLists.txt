find_package(Catch2 3)
if(NOT Catch2_FOUND)
    cpmaddpackage("gh:catchorg/Catch2#8ac8190e494a381072c89f5e161b92a08d98b37b"
    )# v3.5.3
endif()

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
add_subdirectory(components)
add_subdirectory(map)
add_subdirectory(queries)
add_subdirectory(systems)
add_subdirectory(vector2d)

