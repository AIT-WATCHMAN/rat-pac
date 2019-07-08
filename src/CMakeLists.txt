# CMakeLists.txt for the ratpac library code
# Author: Miles Lucas

###########################################################
# Go through each module and get their targets

add_subdirectory(cmd)
add_subdirectory(core)
add_subdirectory(daq)
add_subdirectory(db)
add_subdirectory(ds)
add_subdirectory(fit)
add_subdirectory(gen)
add_subdirectory(geo)
add_subdirectory(io)
add_subdirectory(physics)
add_subdirectory(stlplus)
add_subdirectory(util)

###########################################################
# Create our libraries and executables

# RAT shared library
add_library(RATPAC)
target_link_libraries(RATPAC PUBLIC 
       ${ROOT_LIBRARIES} ${Geant4_LIBRARIES} Threads::Threads
       cmd core daq db ds fit _bonsai gen geo io physics stlplus util RATDict)


### Target: Shared library for ROOT
add_library(RATEvent)
target_link_libraries(RATEvent PUBLIC 
       ${Geant4_LIBRARIES} ${ROOT_LIBRARIES}
       core ds db io util stlplus RATDict)

add_custom_command(
       TARGET RATEvent POST_BUILD
       COMMAND ${CMAKE_COMMAND} -E copy
                     ${CMAKE_CURRENT_BINARY_DIR}/ds/libRATDict_rdict.pcm
                     ${CMAKE_CURRENT_BINARY_DIR}/ds/libRATDict.rootmap
                     ${PROJECT_BINARY_DIR}/lib)

set_target_properties(RATPAC RATEvent 
    PROPERTIES
       ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
       LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Make sure we don't overwrite original root
# if(EXISTS "${CMAKE_INSTALL_PREFIX}/bin/root")
#        message("Renaming the original root binary to root.old")
#        file(RENAME ${CMAKE_INSTALL_PREFIX}/bin/root ${CMAKE_INSTALL_PREFIX}/bin/root.old)
# endif()

install(TARGETS RATPAC RATEvent
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

### Install the global headers
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include 
       DESTINATION ${CMAKE_INSTALL_PREFIX})
