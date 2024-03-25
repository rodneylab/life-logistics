add_executable(MapTests Map.cpp ${PROJECT_SOURCE_DIR}/src/map.cpp
                        ${PROJECT_SOURCE_DIR}/src/templates.cpp)

target_link_libraries(
    MapTests PRIVATE Catch2::Catch2WithMain spdlog::spdlog_header_only
                     life_logistics_compiler_flags)
target_compile_definitions(MapTests PRIVATE SPDLOG_FMT_EXTERNAL)
target_include_directories(MapTests PUBLIC "${PROJECT_SOURCE_DIR}/src")

include(Catch)
catch_discover_tests(MapTests)
