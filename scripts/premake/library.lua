--
libraries = { }
third_party_libraries = { }

function library(_name)
	local module_path = path.join("ExWorkshop", _name.. ".lua") -- TODO: %{prj.name}
	local dofunc = dofile(module_path)

	group("Libraries")
	project(_name)

	kind("StaticLib")
	location("build/%{_ACTION}")

	pcall(dofunc)

	table.insert(libraries, _name)
end

function third_party_library(_name)
	local module_path = path.join("ExWorkshop/third_party", _name.. ".lua") -- TODO: %{prj.name}
	local dofunc = dofile(module_path)

	group("ThirdParty")
	project(_name)

	kind("StaticLib")
	location("build/%{_ACTION}")

	pcall(dofunc)

	table.insert(third_party_libraries, _name)
end
