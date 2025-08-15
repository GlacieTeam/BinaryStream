add_rules("mode.debug", "mode.release")

if is_plat("windows") then
    if not has_config("vs_runtime") then
        set_runtimes("MD")
    end
else
    set_toolchains("clang")
end

option("kind")
    set_default("static")
    set_values("static", "shared")
    set_showmenu(true)
option_end()

target("BinaryStream")
    set_kind("$(kind)")
    set_languages("c++23")
    set_exceptions("none")
    add_includedirs("include")
    add_files("src/**.cpp")
    if is_mode("debug") then
        set_symbols("debug")
    else
        set_optimize("aggressive")
        set_strip("all")
    end
    if is_config("kind", "shared") then
        add_defines("BINARY_STREAM_EXPORT")
    end
    
    if is_plat("windows") then
        add_defines(
            "NOMINMAX",
            "UNICODE"
        )
        add_cxflags(
            "/EHsc",
            "/utf-8",
            "/W4"
        )
        if is_mode("release") then
            add_cxflags(
                "/O2",
                "/Ob3"
            )
        end
    else
        add_cxflags(
            "-Wall",
            "-pedantic",
            "-fexceptions",
            "-stdlib=libc++",
            "-fPIC"
        )
        add_ldflags(
            "-stdlib=libc++"
        )
        if is_mode("release") then
            add_cxflags(
                "-O3"
            )
        end
        if is_config("kind", "shared") then
            add_cxflags(
                "-fvisibility=hidden",
                "-fvisibility-inlines-hidden"
            )
            if is_plat("linux") then
                add_syslinks("c++")
            else
                add_ldflags("-dynamiclib")
            end
        end
    end
    if is_config("kind", "shared") then
        after_build(function (target)
            local output_dir = path.join(os.projectdir(), "bin")
            os.mkdir(output_dir)
            local target_file = target:targetfile()
            local filename = path.filename(target_file)
            local output_path = path.join(output_dir, filename)
            os.cp(target_file, output_path)
            if os.host() == "macosx" then
                os.run("install_name_tool -id @rpath/" .. filename .. " " .. output_path)
            end
            cprint("${bright green}[Shared Library]: ${reset}".. filename .. " already generated to " .. output_dir)
        end)
    end