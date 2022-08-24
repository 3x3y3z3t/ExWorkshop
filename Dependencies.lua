--

VulkanSDKDir = os.getenv("VULKAN_SDK")

vendorDir = "%{wks.location}/ExWorkshop/vendor"

IncludeDir = {}
IncludeDir["glad"] = "%{vendorDir}/glad/include"
IncludeDir["glfw"] = "%{vendorDir}/glfw/include"
IncludeDir["glm"] = "%{vendorDir}/glm"
IncludeDir["shaderc"] = "%{vendorDir}/shaderc/include"
IncludeDir["spdlog"] = "%{vendorDir}/spdlog/include"
IncludeDir["spirv_cross"] = "%{vendorDir}/SPIRV-Cross"
IncludeDir["vulkan_sdk"] = "%{VulkanSDKDir}/Include"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VulkanSDKDir}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["shaderc_dbg"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["spirv_cross_dbg"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["spirv_cross_glsl_dbg"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["spirv_tools_dbg"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["shaderc_rel"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["spirv_cross_rel"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["spirv_cross_glsl_rel"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
