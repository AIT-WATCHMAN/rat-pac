add_library(stlplus OBJECT
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

install(DIRECTORY include # source directory
        DESTINATION include/${PROJECT_NAME} # target directory
        FILES_MATCHING PATTERN "*.hh")
