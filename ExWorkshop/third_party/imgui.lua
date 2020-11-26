--
return function()
	warnings "Off"

	includedirs
	{
		"ExWorkshop/third_party/imgui/",
	}

	files
	{
		"ExWorkshop/third_party/imgui/imconfig.h",
		"ExWorkshop/third_party/imgui/imgui.h",
		"ExWorkshop/third_party/imgui/imgui.cpp",
		"ExWorkshop/third_party/imgui/imgui_draw.cpp",
		"ExWorkshop/third_party/imgui/imgui_internal.h",
		"ExWorkshop/third_party/imgui/imgui_widgets.cpp",
		"ExWorkshop/third_party/imgui/imstb_rectpack.h",
		"ExWorkshop/third_party/imgui/imstb_textedit.h",
		"ExWorkshop/third_party/imgui/imstb_truetype.h",
		"ExWorkshop/third_party/imgui/imgui_demo.cpp",
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
