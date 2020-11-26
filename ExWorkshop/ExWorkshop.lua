--
require("library")

return function()
	warnings "Off"

	links(third_party_libraries)

	pchheader "expch.h"
	pchsource "%{prj.name}/src/expch.cpp"

	sysincludedirs {
		"%{wks.location}/ExWorkshop/include",
		"%{wks.location}/ExWorkshop/src",
    }

	includedirs {
		"%{prj.name}/third_party/entt",
		"%{prj.name}/third_party/glad/include",
		"%{prj.name}/third_party/glfw/include",
		"%{prj.name}/third_party/glm/",
        "%{prj.name}/third_party/imgui",
		"%{prj.name}/third_party/spdlog/include",
        "%{prj.name}/third_party/stb_image",
        "%{prj.name}/third_party/yaml_cpp/include",
		"%{prj.location}/third_party/minimp3_s",
		"%{prj.location}/third_party/openal-soft/include",
		"%{prj.location}/third_party/openal-soft/src",
		"%{prj.location}/third_party/openal-soft/src/common",
	}

	files {
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		
		"%{prj.name}/third_party/glm/glm/**.hpp",
		"%{prj.name}/third_party/glm/glm/**.inl",
		"%{prj.name}/third_party/stb_image/**.h",
		"%{prj.name}/third_party/stb_image/**.cpp",
	}

	vpaths {
		-- For some reason, the token "%{prj.name}" doesn't work with vpaths
		["Header Files/*"] = "include/" .. _name .. "/*",
		["Source Files/*"] = "src/" .. _name .. "/*",
	}

	defines {
		"AL_LIBTYPE_STATIC",
	}

	filter("system:macosx or ios")
		files { "src/%{prj.name}/**.mm" }

	filter { "system:macosx or ios", "files:**.cpp" }
		compileas "Objective-C++"

	filter { }

	table.insert(libraries, _name)
end
