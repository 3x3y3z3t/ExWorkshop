--
require('vstudio')

premake.api.register {
    name = "solution_items",
    scope = "workspace",
    kind = "list:string",
}

premake.override(premake.vstudio.vs2017, "projects", function(_base, _workspace)
    if _workspace.solution_items and #_workspace.solution_items > 0 then
        local solutionFolderGUID = "{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}" -- See https://www.codeproject.com/Reference/720512/List-of-Visual-Studio-Project-Type-GUIDs
        premake.push("Project(\"" .. solutionFolderGUID .. "\") = \"Solution Items\", \"Solution Items\", \" {" .. os.uuid("Solution Items:" .. _workspace.name) .. "}\"")
        premake.push("ProjectSection(SolutionItems) = preProject")

        for _, path in ipairs(_workspace.solution_items) do
            premake.w(path .. " " .. path)
        end

        premake.pop("EndProjectSection")
        premake.pop("EndProject")
    end
    
    _base(_workspace)
end)
