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
            links { "opengl32", "GLFWDLL", "FreeImage" }

            includedirs {
                "dependencies/glfw-2.7.3/include",
                "dependencies/glew-1.7.0/include",
                "dependencies/freeimage-3.15.2/include",
                "dependencies/freetype-2.4.9/include"
            }

            libdirs { 
                "dependencies/glfw-2.7.3/lib-msvc100",
                "dependencies/glew-1.7.0/lib-msvc100",
                "dependencies/freeimage-3.15.2/lib-msvc100",
                "dependencies/freetype-2.4.9/lib-msvc100"
            }

            configuration { "debug", "windows" }
                links { "glew32d", "freetype2-d" }

            configuration { "release", "windows" }
                links { "glew32", "freetype2" }

        configuration "linux"
            links { "rt", "GL", "glfw", "GLEW", "freeimage", "freetype" }