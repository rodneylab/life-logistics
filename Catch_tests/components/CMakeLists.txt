add_executable(ComponentsTests Components.cpp
                               ${PROJECT_SOURCE_DIR}/src/templates.cpp)

target_link_libraries(ComponentsTests INTERFACE life_logistics_compiler_flags)
target_link_libraries(ComponentsTests PRIVATE Catch2::Catch2WithMain)
target_include_directories(ComponentsTests PUBLIC "${PROJECT_SOURCE_DIR}/src")

include(Catch)
catch_discover_tests(ComponentsTests)
