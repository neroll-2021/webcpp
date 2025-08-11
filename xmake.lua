set_xmakever("2.9.7")
set_project("webcpp")
set_version("0.1.0")

set_allowedplats("linux")
set_allowedmodes("debug", "release")

add_rules("mode.debug", "mode.release")

option("disable_exception", { default = false, description = "Disable exceptions" })

set_languages("c++23")
set_warnings("allextra", "error")

target("webcpp")
    set_kind("binary")
    add_includedirs("include")
    add_files("src/*.cpp")
    if has_config("disable_exception") then
        add_defines("WEBCPP_NO_EXCEPTION")
        add_links("stdc++exp")
    end