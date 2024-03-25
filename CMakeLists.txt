cmake_minimum_required(VERSION 3.16)
project(
    LifeLogistics
    VERSION 0.0.1
    DESCRIPTION "Top-down 2D puzzle game"
    LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
add_library(life_logistics_compiler_flags INTERFACE)
target_compile_features(life_logistics_compiler_flags INTERFACE cxx_std_17)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

if(DEFINED EMSCRIPTEN)
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -s -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1 -s ALLOW_MEMORY_GROWTH=1 -s STACK_SIZE=1mb -s EXPORTED_RUNTIME_METHODS=cwrap"
    )
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(
    life_logistics_compiler_flags
    INTERFACE
        "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-pedantic-errors;-Werror;-Wall;-Weffc++;-Wextra;-Wconversion;-Wsign-conversion>>"
        "$<${msvc_cxx}:$<BUILD_INTERFACE:-W4>>")


if(NOT DEFINED EMSCRIPTEN)
    include(cmake/StaticAnalysers.cmake)
    enable_clang_tidy()

    set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")
    option(RUN_TESTS "Enable tests" ON)
    include(coverage)
    add_coverage_target("Catch_tests/*")
endif()

include(Dependencies.cmake)
life_logistics_setup_dependencies()

include(GenerateExportHeader)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

add_library(Vector2D_lib STATIC "${PROJECT_SOURCE_DIR}/src/vector2d.cpp"
                                "${PROJECT_SOURCE_DIR}/src/templates.cpp")
set_target_properties(Vector2D_lib PROPERTIES CXX_CLANG_TIDY
                                              "${CLANG_TIDY_COMMAND}")
target_link_libraries(Vector2D_lib life_logistics_compiler_flags)

add_executable(LifeLogistics src/main.cpp src/map.cpp src/systems.cpp)
set_target_properties(LifeLogistics PROPERTIES CXX_CLANG_TIDY
                                               "${CLANG_TIDY_COMMAND}")
target_link_libraries(
    LifeLogistics
    PRIVATE dbg_macro
            flecs::flecs_static
            fmt
            raylib
            spdlog::spdlog_header_only
            Vector2D_lib
            life_logistics_compiler_flags)
target_include_directories(LifeLogistics PUBLIC "${PROJECT_BINARY_DIR}")
target_compile_definitions(
    LifeLogistics PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

option(RUN_UNIT_TESTS "Run Catch2 unit tests" ON)
if(RUN_UNIT_TESTS)
    enable_testing()
    add_subdirectory(Catch_tests)
endif()

add_subdirectory(docs)
