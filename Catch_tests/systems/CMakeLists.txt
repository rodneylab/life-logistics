add_executable(
    SystemsTests
    Systems.cpp
    ${PROJECT_SOURCE_DIR}/src/map.cpp
    ${PROJECT_SOURCE_DIR}/src/systems.cpp
    ${PROJECT_SOURCE_DIR}/src/templates.cpp)

target_link_libraries(SystemsTests INTERFACE life_logistics_compiler_flags)
target_link_libraries(
    SystemsTests
    PRIVATE Catch2::Catch2WithMain
            flecs::flecs_static
            fmt
            raylib
            spdlog::spdlog_header_only)
target_include_directories(SystemsTests PUBLIC "${PROJECT_SOURCE_DIR}/src")

include(Catch)
catch_discover_tests(SystemsTests)
