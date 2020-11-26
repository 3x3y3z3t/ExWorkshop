--
return function()
	warnings "Off"

	includedirs
	{
		"ExWorkshop/third_party/yaml_cpp/include",
	}

	files
	{
		"ExWorkshop/third_party/yaml_cpp/include/**.h",
		"ExWorkshop/third_party/yaml_cpp/src/**.h",
		"ExWorkshop/third_party/yaml_cpp/src/**.cpp",
	}

	excludes
	{
	}

	defines
	{
	}

	filter { "system:windows" }
		systemversion("latest")
		
	filter { "system:linux" }
		pic "On"
end
