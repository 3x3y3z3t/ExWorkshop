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

    IncludeDir = {}
	IncludeDir["entt"] = "%{wks.location}/ExWorkshop/vendor/entt"
    IncludeDir["glfw"] = "%{wks.location}/ExWorkshop/vendor/glfw/include"
    IncludeDir["glm"] = "%{wks.location}/ExWorkshop/vendor/glm"
    IncludeDir["glad"] = "%{wks.location}/ExWorkshop/vendor/glad/include"
    IncludeDir["spdlog"] = "%{wks.location}/ExWorkshop/vendor/spdlog/include"
	IncludeDir["stb_image"] = "%{wks.location}/ExWorkshop/vendor/stb_image"

group "Dependencies"
	include "vendor/premake"
	include "ExWorkshop/vendor/GLFW"
	include "ExWorkshop/vendor/Glad"
    
group ""
    include "ExWorkshop"
    include "Sandbox"

