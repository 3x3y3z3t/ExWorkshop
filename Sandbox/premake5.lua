project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/ExWorkshop/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}",
	}

	links
	{
		"ExWorkshop"
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
		optimize "on"

	filter "configurations:Dist"
		defines "EXW_DST"
		runtime "Release"
		optimize "on"
		