add_library(stlplus STATIC
        src/file_system.cc
        src/fileio.cc
        src/persistent.cc
        src/exceptions.cc
        src/debug.cc
        src/os_fixes.cc
        src/textio.cc
        src/string_utilities.cc
        src/multiio.cc
        src/dprintf.cc
        src/stringio.cc)

target_include_directories(stlplus PRIVATE include)
