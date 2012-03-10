solution "shmup"
    configurations { "Debug", "Release" }

    project "shmup"
        kind "ConsoleApp"
        language "C++"
        files { "*.h", "*.cpp" }
        buildoptions { "-Wall" }
        links { "sfml-graphics", "sfml-window", "sfml-audio", "sfml-system" }



