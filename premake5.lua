include "./vendor/premake/customization/solution_items.lua"

workspace "ExWorkshop"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

    outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

    -- Include directories relative to root folder (solution directory)
    IncludeDir = {}
    IncludeDir["GLFW"] = "%{wks.location}/ExWorkshop/vendor/GLFW/include"
    IncludeDir["spdlog"] = "%{wks.location}/ExWorkshop/vendor/spdlog/include"

group "Dependencies"
	include "vendor/premake"
	include "ExWorkshop/vendor/GLFW"
    
group ""
    include "ExWorkshop"
    include "Sandbox"

