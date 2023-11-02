set_project("vect")

includes("rules.lua", "test/xmake.lua")

-- Compiler setup
add_rules("mode.release", "mode.debug")
add_cflags("-Wall", "-Werror", "-Wextra")
set_languages("c11")
add_toolchains("gcc")

target("vect")
  set_default()
  set_kind("static")
  add_files("vect.c", "common.c")
  add_headerfiles("vect.h", "common.h")

  add_rules("coverage")
target_end()
