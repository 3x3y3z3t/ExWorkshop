--
return function()
	warnings "Off"

	includedirs {
		"ExWorkshop/third_party/glfw/include",
	}

	files {
		"ExWorkshop/third_party/glfw/include/GLFW/glfw3.h",
		"ExWorkshop/third_party/glfw/include/GLFW/glfw3native.h",
		"ExWorkshop/third_party/glfw/src/context.c",
		"ExWorkshop/third_party/glfw/src/glfw_config.h",
		"ExWorkshop/third_party/glfw/src/init.c",
		"ExWorkshop/third_party/glfw/src/input.c",
		"ExWorkshop/third_party/glfw/src/monitor.c",
		"ExWorkshop/third_party/glfw/src/vulkan.c",
		"ExWorkshop/third_party/glfw/src/window.c",
	}

	filter { "system:windows" }
		files {
			"ExWorkshop/third_party/glfw/src/egl_context.c",
			"ExWorkshop/third_party/glfw/src/osmesa_context.c",
			"ExWorkshop/third_party/glfw/src/wgl_context.c",
			"ExWorkshop/third_party/glfw/src/win32_init.c",
			"ExWorkshop/third_party/glfw/src/win32_joystick.c",
			"ExWorkshop/third_party/glfw/src/win32_monitor.c",
			"ExWorkshop/third_party/glfw/src/win32_time.c",
			"ExWorkshop/third_party/glfw/src/win32_thread.c",
			"ExWorkshop/third_party/glfw/src/win32_window.c",
		}

		defines { 
			"_GLFW_WIN32",
		}

		links { "opengl32.lib" }

	filter { "system:linux" }
		files {
			"ExWorkshop/third_party/glfw/src/egl_context.c",
			"ExWorkshop/third_party/glfw/src/glx_context.c",
			"ExWorkshop/third_party/glfw/src/linux_joystick.c",
			"ExWorkshop/third_party/glfw/src/osmesa_context.c",
			"ExWorkshop/third_party/glfw/src/posix_thread.c",
			"ExWorkshop/third_party/glfw/src/posix_time.c",
			"ExWorkshop/third_party/glfw/src/x11_init.c",
			"ExWorkshop/third_party/glfw/src/x11_monitor.c",
			"ExWorkshop/third_party/glfw/src/xkb_unicode.c",
			"ExWorkshop/third_party/glfw/src/x11_window.c",
		}

		defines {
			"_GLFW_X11",
		}

	filter { }
end
