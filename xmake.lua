-- xmake.lua

set_project("bagla-engine")

set_languages("c++17")

add_rules("mode.debug", "mode.release")

add_requires("sfml", "spdlog", "box2d", "tweeny", "tmxlite")

target("bagla-engine")
    set_kind("shared")

    -- Add source files
    add_files("src/**.cpp")

    -- Add header files
    add_headerfiles("include/(bagla-engine/**.h)")

    -- Set include directories to match your current structure
    add_includedirs("include")
    add_includedirs("include/bagla-engine")

    -- Add packages
    add_packages("sfml", "spdlog", "box2d", "tweeny", "tmxlite")
