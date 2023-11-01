add_rules("mode.release", "mode.debug")

add_cflags("-Wall", "-Werror", "-Wextra")
set_languages("c11")

add_toolchains("gcc")
