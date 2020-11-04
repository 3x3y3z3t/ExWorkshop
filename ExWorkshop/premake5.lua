project "ExWorkshop"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_int/" .. outputdir .. "/%{prj.name}")

	pchheader "expch.h"
	pchsource "src/expch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
	}

	defines
	{
        "_CRT_SECURE_NO_WARNINGS",
        "EXW_CORE_LIB",
        "GLFW_INCLUDE_NONE",
	}

	includedirs
	{
        "src",
        "%{IncludeDir.entt}",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.spdlog}",
		"%{IncludeDir.stb_image}",
	}

	links
	{
        "GLFW",
        "Glad",
        "opengl32.lib",
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

	filter "configurations:Release"
		defines "EXW_REL"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EXW_DST"
		runtime "Release"
        optimize "on"
        