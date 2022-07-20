--
project "Premake"
    kind "Utility"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{wks.location}/**premake5.lua"
    }

    postbuildmessage "Generating project files with Premake5.."
    postbuildcommands {
        "\"%{prj.location}..\\..\\vendor\\premake\\bin\\premake5\" %{_ACTION} --file=\"%{wks.location}premake5.lua\""
    }