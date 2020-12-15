--
require("scripts/premake/customizations")
require("scripts/premake/defaults")
require("scripts/premake/options")
require("scripts/premake/settings")
require("scripts/premake/target")
require("scripts/premake/utils")

require("scripts/premake/library")

require("scripts/premake/app")

workspace(settings.workspace_name)
platforms(utils.get_platforms())
configurations({ "Debug", "Release" })

third_party_library("glad")
third_party_library("glfw")
third_party_library("imgui")
third_party_library("yaml-cpp")

third_party_library("openal-soft")

library("ExWorkshop", { settings.extDefExwExperimental })
app("ExToolbox", { settings.extDefExwExperimental })
app("Sandbox", { settings.extDefExwExperimental, settings.extDefRuntime })

-- Set last app as startup
workspace(settings.workspace_name)
startproject(apps["ExToolbox"])
