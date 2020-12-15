--
require("library")

apps = { }

function app(_name, _extDefines)
	group("Apps")
	project(_name)

	debugdir "%{prj.name}/res"
	links { libraries }
	location("build/%{_ACTION}")
	xcodebuildresources("%{prj.name}/res")

	sysincludedirs {
		"%{wks.location}/ExWorkshop/include",
    }
    
    includedirs {
        "%{wks.location}/ExWorkshop/third_party/entt/",
        "%{wks.location}/ExWorkshop/third_party/glm",
        "%{wks.location}/ExWorkshop/third_party/spdlog/include",
		"%{wks.location}/ExWorkshop/third_party/entt",
		"%{wks.location}/ExWorkshop/third_party/glad/include",
		"%{wks.location}/ExWorkshop/third_party/glfw/include",
		"%{wks.location}/ExWorkshop/third_party/glm/",
        "%{wks.location}/ExWorkshop/third_party/imgui",
		"%{wks.location}/ExWorkshop/third_party/spdlog/include",
        "%{wks.location}/ExWorkshop/third_party/stb_image",
        "%{wks.location}/ExWorkshop/third_party/yaml_cpp/include",
		"%{prj.location}/third_party/minimp3_s",
		"%{prj.location}/third_party/openal-soft/include",
		"%{prj.location}/third_party/openal-soft/src",
		"%{prj.location}/third_party/openal-soft/src/common",
    }

	files {
		"%{wks.location}/" .._name.. "/src/**.h",
		"%{wks.location}/" .._name.. "/src/**.cpp",
    }

	defines {
		_extDefines	
	}

	filter { "system:linux" }
		linkoptions { "-pthread -Wl,-rpath=\\$$ORIGIN" }
		links {
			"dl",
		}

	filter { "system:ios" }
		files { "src/%{prj.name}/Resources/Info.plist", "src/%{prj.name}/res" }

	filter { "system:macosx or ios", "files:**.cpp" }
		compileas "Objective-C++"

	filter { "configurations:Debug" }
        kind("ConsoleApp")
        defines {
            "EXW_DBG",
        }

	filter { "configurations:Release" }
        kind("WindowedApp")
        -- kind("ConsoleApp")
        defines {
            "EXW_REL"
        }

	filter { }

	table.insert(apps, _name)
end