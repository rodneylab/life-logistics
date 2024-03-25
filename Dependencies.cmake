include(cmake/CPM.cmake)

function(life_logistics_setup_dependencies)
  include(cmake/CPM.cmake)
  cpmaddpackage("gh:sharkdp/dbg-macro#fb9976f410f8b29105818b20278cd0be0e853fe8"
  )# v0.5.1
  cpmaddpackage(
    "gh:SanderMertens/flecs#198607d10ab8f8fc44540043271d6e3be019250b") # v3.2.11
  cpmaddpackage("gh:fmtlib/fmt#e69e5f977d458f2650bb346dadf2ad30c5320281") # 10.x
  cpmaddpackage("gh:raysan5/raylib#ae50bfa2cc569c0f8d5bc4315d39db64005b1b0"
  )# v5.0
  cpmaddpackage("gh:gabime/spdlog#7c02e204c92545f869e2f04edaab1f19fe8b19fd"
  )# v1.13.0
endfunction()
