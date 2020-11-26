--
require("customizations")

cppdialect "C++17"
debugdir "%{wks.location}/assets"
exceptionhandling("Off")
flags { "MultiProcessorCompile" }
--includedirs { "%{prj.location}/include/" }
objdir("%{wks.location}/obj")
rtti("Off")
targetdir('../../%{iif(prj.kind == "StaticLib" or prj.kind == "SharedLib","lib","bin")}/%{cfg.platform}/%{cfg.buildcfg}')
warnings "Extra"

filter { "configurations:Debug" }
	optimize "Off"
	symbols "On"
	defines { "_DBG" }

filter { "configurations:Release" }
	optimize "Full"
	symbols "Off"
	defines { "_REL", "NDEBUG" }

filter { "system:windows" }
	toolset("msc")
    defines { 
        "NOMINMAX",
    }

filter { "system:not windows" }
	toolset("gcc")

filter { "system:linux" }
	debugenvs { "LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../%{OUTDIR}" }

filter { }
