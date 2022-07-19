--
include "Dependencies.lua"

workspace "ExWorkshop"
    architecture "x86_64"
    startproject "ExWorkshop"

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

group ""

include "ExWorkshop"
