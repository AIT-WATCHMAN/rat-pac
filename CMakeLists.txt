cmake_minimum_required(VERSION 3.11)
project(rat-pac VERSION 1.0
                DESCRIPTION "Watchman RAT-PAC"
                LANGUAGES CXX Fortran)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

## Set up root
find_package(ROOT CONFIG REQUIRED COMPONENTS Minuit2 PyROOT)
include(${ROOT_USE_FILE})

## Set up Geant4
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})


## Config header
configure_file(${CMAKE_SOURCE_DIR}/config/Config.hh.in
        ${CMAKE_SOURCE_DIR}/include/RAT/Config.hh
        @ONLY NEWLINE_STYLE UNIX)

find_package(Threads REQUIRED)

add_subdirectory(src)
add_subdirectory(tools)

### Install the data
install(DIRECTORY data/ DESTINATION share/GLG4Data
        PATTERN "data/*")

### Install the python files
install(DIRECTORY python/ DESTINATION share/python
        PATTERN "python/*")

### Install the mac files
install(DIRECTORY mac/ DESTINATION share/mac
        PATTERN "mac/*")

### Install the doc files
install(DIRECTORY doc/ DESTINATION share/RAT/doc
        PATTERN "doc/*")

### Install the env files
configure_file(${CMAKE_SOURCE_DIR}/config/ratpac.sh.in
       ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ratpac.sh
       @ONLY NEWLINE_STYLE UNIX)
configure_file(${CMAKE_SOURCE_DIR}/config/ratpac.csh.in
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ratpac.csh
       @ONLY NEWLINE_STYLE UNIX)
install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ratpac.sh
             ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ratpac.csh
       DESTINATION bin)
