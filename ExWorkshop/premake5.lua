--
project "ExWorkshop"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin/int/" .. outputdir .. "/%{prj.name}")

    pchheader "expch.h"
    pchsource "src/expch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",

    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "EXW_CORE_LIB",
    }

    includedirs
    {
        "src",
    }

    links
    {
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
        }

    filter "configurations:Debug"
        defines "EXW_DBG"
        runtime "Debug"
        symbols "on"

        links
        {
        }

    filter "configurations:Release"
        defines "EXW_REL"
        runtime "Release"
        optimize "on"

        links
        {
        }

    filter "configurations:Dist"
        defines "EXW_DST"
        runtime "Release"
        optimize "on"

        links
        {
        }
