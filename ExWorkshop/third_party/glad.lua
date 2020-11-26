--
return function()
	warnings "Off"

	includedirs {
		"ExWorkshop/third_party/glad/include",
	}

	files {
		"ExWorkshop/third_party/glad/include/glad/glad.h",
		"ExWorkshop/third_party/glad/include/KHR/khrplatform.h",
		"ExWorkshop/third_party/glad/src/glad.c",
	}
end
