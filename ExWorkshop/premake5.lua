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
        "%{IncludeDir.stb_image}/**.h",
        "%{IncludeDir.stb_image}/**.cpp",
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
    }

    includedirs {
        "src",
        "%{IncludeDir.glad}",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.vulkan_sdk}",
    }
    
    -- externalincludedirs {
    --     "%{IncludeDir.spdlog}",
    --     "%{IncludeDir.glfw}"
    -- }

    libdirs {

    }

    links {
        "Glad",
        "GLFW",
        "opengl32.lib"
    }

    -- flags {
    --     "NoPCH"
    -- }

    -- externalwarnings "off"
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "EXW_DBG"
        runtime "Debug"
        symbols "on"

        links {
            "%{Library.shaderc_dbg}",
            "%{Library.spirv_cross_dbg}",
            "%{Library.spirv_cross_glsl_dbg}"
        }

    filter "configurations:Release"
        defines "EXW_REL"
        runtime "Release"
        symbols "on"

        links {
            "%{Library.shaderc_rel}",
            "%{Library.spirv_cross_rel}",
            "%{Library.spirv_cross_glsl_rel}"
        }

    filter "configurations:Dist"
        defines "EXW_DST"
        runtime "Release"
        symbols "off"
        optimize "on"

        links {
            "%{Library.shaderc_rel}",
            "%{Library.spirv_cross_rel}",
            "%{Library.spirv_cross_glsl_rel}"
        }
