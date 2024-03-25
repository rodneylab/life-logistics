add_executable(
    QueriesTests
    Queries.cpp
    ${PROJECT_SOURCE_DIR}/src/map.cpp
    ${PROJECT_SOURCE_DIR}/src/systems.cpp
    ${PROJECT_SOURCE_DIR}/src/templates.cpp)

target_link_libraries(QueriesTests INTERFACE life_logistics_compiler_flags)
target_link_libraries(
    QueriesTests
    PRIVATE Catch2::Catch2WithMain
            flecs::flecs_static
            fmt
            raylib
            spdlog::spdlog_header_only)
target_include_directories(QueriesTests PUBLIC "${PROJECT_SOURCE_DIR}/src")

include(Catch)
catch_discover_tests(QueriesTests)
