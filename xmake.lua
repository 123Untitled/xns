-- minimal xmake version
set_xmakever("2.8.1")

-- allowed platforms
set_allowedplats("macosx")

-- set project
set_project("xns")


-- set version
set_version("0.1.0", {build = "%Y%m%d%H%M"})

-- add debug and release modes
add_rules("mode.debug", "mode.release")

-- default mode
set_defaultmode("debug")

-- set optimization: none, faster, fastest, smallest
if is_mode("debug") then
	set_optimize("none")
end
if is_mode("release") then
	set_optimize("fastest")
end

-- set language
set_languages("cxx23")

-- flags
add_cxxflags("-Wall", "-Wextra", "-Werror", "-Wpedantic", "-Wno-unused", "-Wno-unused-variable", "-Wno-unused-parameter",
		"-Winline", "-Weffc++", "-Wconversion", "-Wsign-conversion", "-Wfloat-conversion", "-Wnarrowing", "-Wshadow")



-- get source files
local src = os.files("src/**")

-- get include directories
local inc = os.dirs("inc/**")
inc = table.join("inc", inc)

-- output directory
set_targetdir(".")


-- static library
target("xns_static", function()
	-- set name
	set_basename("xns")
	set_kind("static")
	add_files(src)
	add_includedirs(inc)
end)


-- executable file
target("xns_exec", function()
    -- set name
	set_basename("xnsexec")
    set_kind("binary")
	add_deps("xns_static")
end)


-- shared library
target("xns_shared", function()
    -- set name
	set_basename("xns")
	set_kind("shared")
	add_deps("xns_static")
end)


-- full clean
task("fclean")
	-- Set the run script
	on_run(function()
		-- call xmake clean
		os.exec("xmake clean")
		os.rm("build")
		os.rm("compile_commands.json")
		os.rm(".cache")
		os.rm(".xmake")
	end)
    -- Set the command line options for the plugin. There are no parameter options here, just the plugin description.
    set_menu {}


-- compile commands
task("ccdb")
	-- Set the run script
	on_run(function()
		-- call xmake compile_commands
		os.exec("xmake project -k compile_commands")
	end)
	-- Set the command line options for the plugin. There are no parameter options here, just the plugin description.
	set_menu {}

