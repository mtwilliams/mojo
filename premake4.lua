solution "mojo"
    location "build"
    configurations { "debug", "release", "windows", "linux" }
    
    defines { "MOJO_STATIC_BUILD" }

    project "mojo"
        kind "ConsoleApp"
        language "C++"
        targetdir "bin"

        includedirs { 
            "include"
        }

        files {
            "include/**.h",
            "include/**.hpp",
            "source/**.c",
            "source/**.cpp",
        }

        configuration "debug"
            targetsuffix "d"
            defines { "MOJO_DEBUG_BUILD" }
            flags { "Symbols" }

        configuration "release"
            defines { "MOJO_RELEASE_BUILD" }
            flags { "Optimize" }

        configuration "windows"
            defines { "GLFW_DLL" }
            links { "opengl32", "GLFWDLL", "glew32" }

            includedirs {
                "dependencies/glfw-2.7.3/include",
                "dependencies/glew-1.7.0/include",
            }

            libdirs { 
                "dependencies/glfw-2.7.3/lib-msvc100",
                "dependencies/glew-1.7.0/lib-msvc100",
            }

            configuration { "debug", "windows" }
                links { "glew32d" }

            configuration { "release", "windows" }
                links { "glew32" }

        configuration "linux"
            links { "GL", "glfw", "GLEW" }