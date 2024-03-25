add_executable(
    QueriesTests
    Queries.cpp
    ${PROJECT_SOURCE_DIR}/src/map.cpp
    ${PROJECT_SOURCE_DIR}/src/systems.cpp
    ${PROJECT_SOURCE_DIR}/src/templates.cpp)

target_link_libraries(
    QueriesTests
    PRIVATE Catch2::Catch2WithMain
            flecs::flecs_static
            fmt
            raylib
            spdlog::spdlog_header_only
            life_logistics_compiler_flags)
target_compile_definitions(QueriesTests PRIVATE SPDLOG_FMT_EXTERNAL)
target_include_directories(QueriesTests PUBLIC "${PROJECT_SOURCE_DIR}/src")

include(Catch)
catch_discover_tests(QueriesTests)
