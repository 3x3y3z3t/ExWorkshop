project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/ExWorkshop/src",
        "%{IncludeDir.spdlog}",
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
        symbols "off"
		optimize "on"
		