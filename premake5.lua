workspace "JonesyEngine"
    configurations { "Debug", "Release" }
    architecture "x64"
    startproject "Engine"

project "Engine"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/%{cfg.buildcfg}")

    files {
        "src/**.cpp",
        "src/**.c",
        "src/**.h",
        "src/Shaders/**.frag",
        "src/Shaders/**.vert",
        "src/Textures**.jpg",
        "Dependencies/ImGui/**.cpp",
        "Dependencies/ImGui/**.h",
    }

    includedirs {
        "Dependencies",
        "Dependencies/GLFW/include",
        "Dependencies/glm",
        "Dependencies/Glad/include",
        "Dependencies/ImGui",
    }

    links {
        "opengl32",
        "glfw"
    }

    libdirs {
        path.getabsolute("Dependencies/GLFW/lib"),
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"