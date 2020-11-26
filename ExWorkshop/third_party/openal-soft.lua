--
return function()
	warnings "Off"

	includedirs
	{
		"ExWorkshop/third_party/openal_soft/src",
		"ExWorkshop/third_party/openal_soft/src/alc",
		"ExWorkshop/third_party/openal_soft/src/common",
		"ExWorkshop/third_party/openal_soft/include",
		"ExWorkshop/third_party/openal_soft/include/AL",
	}

	files
	{
		"ExWorkshop/third_party/openal_soft/src/**.h",
		"ExWorkshop/third_party/openal_soft/src/**.cpp",
	}

	excludes
	{
		"ExWorkshop/third_party/openal_soft/src/alc/mixer/mixer_neon.cpp",
	}

	defines
	{
		"AL_LIBTYPE_STATIC"
	}

	filter { "system:windows" }
		systemversion("latest")

		defines
		{
			"WIN32",
			"_WINDOWS",
			"AL_BUILD_LIBRARY",
			"AL_ALEXT_PROTOTYPES",
			"_WIN32",
			"_WIN32_WINNT=0x0502",
			"_CRT_SECURE_NO_WARNINGS",
			"NOMINMAX",
			"CMAKE_INTDIR=\"Debug\"",
			"OpenAL_EXPORTS",
		}

		links
		{
			"winmm",
		}
end
