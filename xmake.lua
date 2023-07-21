-- minimal xmake version
set_xmakever("2.8.1")

-- allowed platforms
set_allowedplats("macosx")


-- P R O J E C T --------------------------------------------------------------

-- set project
set_project("xns")

-- set version
set_version("0.1.0", {build = "%Y%m%d%H%M"})


-- R U L E S ------------------------------------------------------------------

-- add debug and release modes
add_rules("mode.debug", "mode.release")

-- default mode
--set_defaultmode("release")


-- set language
set_languages("cxx20")

-- flags
add_cxxflags("-Wall", "-Wextra", "-Werror", "-Wpedantic", "-Wno-unused", "-Wno-unused-variable", "-Wno-unused-parameter",
		"-Winline", "-Weffc++", "-Wconversion", "-Wsign-conversion", "-Wfloat-conversion", "-Wnarrowing", "-Wshadow")


-- output directory
set_targetdir(".")

-- get include directories
local inc = os.dirs("inc/**")
-- append folder
inc = table.join(inc, "inc")

-- get source files
local src = os.files("src/xns/**.cpp")
-- get unit test files
local usrc = os.files("src/unit_tests/**.cpp")


-- mode release
if is_mode("release") then

	-- library target
	target("library", function()

		-- static library
		set_kind("static")
		-- set name
		set_basename("xns")

		-- on install
		on_install(function(target)
			-- build library
			os.exec("xmake")
			print("installing %s", target:targetfile())
			-- create directory
			os.mkdir("xns")
			os.mkdir("xns/include")
			os.mkdir("xns/lib")
			-- copy target file
			os.cp(target:targetfile(), "xns/lib")
			os.cp("inc/xns", "xns/include")
		end)


		add_files(src)
		add_includedirs(inc)

		set_optimize("fastest")



		-- on clean
		on_clean(function(target)
			print("RELEASE: cleaning %s", target:targetfile())
			os.rm("xns")
			os.rm("build")
			os.rm(target:targetfile())
		end)

	end)
end


if is_mode("debug") then

	-- generate and update compile_commands.json
	add_rules("plugin.compile_commands.autoupdate", {outputdir = "."})

	-- executable file
	target("executable", function()
		-- set name
		set_basename("xnsexec")
		set_kind("binary")

		set_optimize("none")

		add_files(src)
		add_files(usrc)
		add_includedirs(inc)
		-- on install
		on_install(function()
			-- print some tips
			print("cannot install debug version")
			-- exiting
			os.exit(1)
		end)

		-- on clean
		on_clean(function(target)
			print("DEBUG: cleaning %s", target:targetfile())
			os.rm("build")
			os.rm(target:targetfile())
			os.rm("compile_commands.json")
		end)

	end)
end

-- full clean
task("fclean")
	-- Set the run script
	on_run(function()
		os.rm("build")
		os.rm("compile_commands.json")
		os.rm(".cache")
		os.rm(".xmake")
	end)
    -- Set the command line options for the plugin. There are no parameter options here, just the plugin description.
    set_menu {}


