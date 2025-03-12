include(cmake/CPM.cmake)

function(life_logistics_setup_dependencies)
    include(cmake/CPM.cmake)
    cpmaddpackage(
        "gh:sharkdp/dbg-macro#fb9976f410f8b29105818b20278cd0be0e853fe8"
    )# v0.5.1
    cpmaddpackage(
        "gh:SanderMertens/flecs#198607d10ab8f8fc44540043271d6e3be019250b"
    )# v3.2.11

    message(STATUS "Include fmtlib")
    cpmaddpackage("gh:fmtlib/fmt#9cf9f38eded63e5e0fb95cd536ba51be601d7fa2"
    )# 11.1.3
    message(STATUS "Added fmtlib with CPM as ${CPM_LAST_PACKAGE_NAME}")

    message(STATUS "Include raylib")
    cpmaddpackage("gh:raysan5/raylib#ae50bfa2cc569c0f8d5bc4315d39db64005b1b0"
    )# v5.0
    message(STATUS "Added raylib with CPM as ${CPM_LAST_PACKAGE_NAME}")

    message(STATUS "Include spdlog")
    cpmaddpackage("gh:gabime/spdlog#f355b3d58f7067eee1706ff3c801c2361011f3d5"
    )# v1.15.1
    message(STATUS "Added spdlog with CPM as ${CPM_LAST_PACKAGE_NAME}")
endfunction()
