--
include "Dependencies.lua"

workspace "ExWorkshop"
    architecture "x86_64"
    startproject "Sandbox"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    flags {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "scripts/premake"
    include "ExWorkshop/vendor/glfw"
    include "ExWorkshop/vendor/glad"

group ""

include "ExWorkshop"
include "Sandbox"
