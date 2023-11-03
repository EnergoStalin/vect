set_project("vect")

add_requires("check")

target("vect-test")
  set_kind("binary")
  add_files("*.c")
  add_headerfiles("*.h")
  add_rules("valgrind", "report")

  add_packages("check")
  add_deps("vect")

  set_group("test")
target_end()
