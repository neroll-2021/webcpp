set_xmakever("2.9.7")
set_project("webcpp")
set_version("0.1.0")

set_allowedplats("linux")
set_allowedmodes("debug", "release")

add_rules("mode.debug", "mode.release")

set_languages("c++23")
set_warnings("allextra", "error")

target("webcpp")
    set_kind("binary")
    add_files("src/*.cpp")