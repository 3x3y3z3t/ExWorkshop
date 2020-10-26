workspace "ExWorkshop"
    architecture "x86_64"
    startproject "Sandbox"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }
    
    flags {
        "MultiProcessorCompile",
    }

    outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["misc"] = "vendor"

group "Dependencies"
    
group ""
    project "ExWorkshop"
        location "ExWorkshop"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "On"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin/int/" .. outputdir .. "/%{prj.name}")
        
        pchheader "expch.h"
        pchsource "ExWorkshop/src/expch.cpp"

        defines {
            "EXW_CORE_LIB",
            "_CRT_SECURE_NO_WARNINGS",
            "GLFW_INCLUDE_NONE",
        }
        
        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
        }

        includedirs {
            "%{prj.name}/src",
        }
        
        libdirs {
        }

        links {
        }

        filter "system:windows"
            systemversion "latest"
            
            defines {
            }
        
        filter "configurations:Debug"
            runtime "Debug"
            symbols "On"
            
            defines {
                "EXW_DBG",
            }
        
        filter "configurations:Release"
            runtime "Release"
            optimize "On"
            
            defines {
                "EXW_REL",
            }
        
        filter "configurations:Dist"
            runtime "Release"
            optimize "On"
            
            defines {
                "EXW_DST",
            }
        
        
    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "On"
        
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin/int/" .. outputdir .. "/%{prj.name}")
        
        defines {
        }
        
        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
        }
        
        includedirs {
            "ExWorkshop/src",
        }
        
        links {
            "ExWorkshop"
        }
        
        filter "system:windows"
            systemversion "latest"
        
        filter "configurations:Debug"
            defines "EXW_DBG"
            runtime "Debug"
            symbols "On"
        
        filter "configurations:Release"
            defines "EXW_REL"
            runtime "Release"
            optimize "On"
        
        filter "configurations:Dist"
            defines "EXW_DST"
            runtime "Release"
            optimize "On"
            