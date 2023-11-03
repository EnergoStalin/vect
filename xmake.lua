set_project("vect")

includes("compiler.lua")
set_compiler_flags()

includes("rules.lua", "test/xmake.lua")

target("vect")
  set_default()
  set_kind("static")
  add_files("vect.c", "common.c")
  add_headerfiles("vect.h", "common.h")

  add_rules("coverage")
target_end()
