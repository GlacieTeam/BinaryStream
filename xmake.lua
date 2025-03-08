add_rules("mode.debug", "mode.release")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

target("BinaryStream")
    set_kind("static")
    set_languages("cxx20")
    set_symbols("debug")   
    set_exceptions("none")
    add_includedirs("include")
    add_defines(
        "NOMINMAX", 
        "UNICODE"
    )
    add_cxflags(
        "/EHa", 
        "/utf-8", 
        "/W4", 
        "/w44265", 
        "/w44289", 
        "/w44296", 
        "/w45263", 
        "/w44738", 
        "/w45204", 
        "/O2", 
        "/Ob3", 
        "/Gy", 
        "/GF"
    )
    add_ldflags(
        "/OPT:REF", 
        "/OPT:ICF"
    )
    add_files("src/*.cpp")