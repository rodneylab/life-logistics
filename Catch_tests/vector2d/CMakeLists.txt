add_executable(Vector2DTests Vector2DTests.cpp
                             ${PROJECT_SOURCE_DIR}/src/templates.cpp)

target_link_libraries(Vector2DTests INTERFACE life_logistics_compiler_flags)
target_link_libraries(Vector2DTests PRIVATE Catch2::Catch2WithMain)
target_include_directories(Vector2DTests PUBLIC "${PROJECT_SOURCE_DIR}/src")

include(Catch)
catch_discover_tests(Vector2DTests)
