###########################################################
# CMakeLists for stlplus module

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

# Set our include directories
target_include_directories(stlplus PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include)

# Copy our headers when installing
file(COPY include/ DESTINATION ${RATPAC_INCDIR})
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include
        DESTINATION ${CMAKE_INSTALL_PREFIX})
