--
project "ExWorkshop"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "exwpch.h"
    pchsource "src/exwpch.cpp"

    files {
        "src/**.h",
        "src/**.cpp",
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
    }

    includedirs {
        "src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glfw}"
    }

    libdirs {

    }

    links {
        "GLFW",
        "opengl32.lib"
    }

    flags {
        "NoPCH"
    }
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "EXW_DBG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "EXW_REL"
        runtime "Release"
        symbols "on"

    filter "configurations:Dist"
        defines "EXW_DST"
        runtime "Release"
        symbols "off"
        optimize "on"
