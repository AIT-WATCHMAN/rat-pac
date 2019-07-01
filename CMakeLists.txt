cmake_minimum_required(VERSION 3.11)
project(rat-pac VERSION 1.0
                DESCRIPTION "Watchman RAT-PAC"
                LANGUAGES CXX)

## Set up root
find_package(ROOT CONFIG REQUIRED)
include(${ROOT_USE_FILE})

## Set up Geant4
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})


add_subdirectory(src)


### Install the source files
#configure_file(${CMAKE_SOURCE_DIR}/config/rat-pac.sh.in
#        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rat-pac.sh
#        @ONLY NEWLINE_STYLE UNIX)
#configure_file(${CMAKE_SOURCE_DIR}/config/rat-pac.csh.in
#        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rat-pac.csh
#        @ONLY NEWLINE_STYLE UNIX)
#install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rat-pac.sh
#              ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rat-pac.csh
#        PERMISSIONS OWNER_WRITE OWNER_READ
#        GROUP_READ
#        WORLD_READ
#        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

### Config header
#configure_file(${CMAKE_SOURCE_DIR}/config/config.hh.in
#        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/include/config.hh
#        @ONLY NEWLINE_STYLE UNIX)


