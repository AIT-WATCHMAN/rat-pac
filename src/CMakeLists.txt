set(RAT_INCDIRS ${PROJECT_SOURCE_DIR}/include
                ${CMAKE_CURRENT_LIST_DIR}/cmd/include
                ${CMAKE_CURRENT_LIST_DIR}/core/include
                ${CMAKE_CURRENT_LIST_DIR}/daq/include
                ${CMAKE_CURRENT_LIST_DIR}/db/include
                ${CMAKE_CURRENT_LIST_DIR}/ds/include
                ${CMAKE_CURRENT_LIST_DIR}/fit/include
                ${CMAKE_CURRENT_LIST_DIR}/gen/include
                ${CMAKE_CURRENT_LIST_DIR}/geo/include
                ${CMAKE_CURRENT_LIST_DIR}/io/include
                ${CMAKE_CURRENT_LIST_DIR}/physics/include
                ${CMAKE_CURRENT_LIST_DIR}/stlplus/include
                ${CMAKE_CURRENT_LIST_DIR}/util/include)

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

# RAT shared library
add_library(RATPAC STATIC
       $<TARGET_OBJECTS:cmd>
       $<TARGET_OBJECTS:core>
       $<TARGET_OBJECTS:daq>
       $<TARGET_OBJECTS:db>
       $<TARGET_OBJECTS:ds>
       $<TARGET_OBJECTS:fit>
       $<TARGET_OBJECTS:_bonsai>
       $<TARGET_OBJECTS:gen>
       $<TARGET_OBJECTS:geo>
       $<TARGET_OBJECTS:io>
       $<TARGET_OBJECTS:physics>
       $<TARGET_OBJECTS:stlplus>
       $<TARGET_OBJECTS:util>
       $<TARGET_OBJECTS:RATDict>)
target_link_libraries(RATPAC PUBLIC ${ROOT_LIBRARIES} ${Geant4_LIBRARIES} Threads::Threads)

# Rat executable
add_executable(rat rat.cc)
target_include_directories(rat PUBLIC ${RAT_INCDIRS})
target_link_libraries(rat PUBLIC RATPAC)

### Target: Shared library for ROOT
add_library(RATEvent SHARED
       core/src/Log.cc
       $<TARGET_OBJECTS:ds>
       $<TARGET_OBJECTS:db>
       io/src/DSReader.cc
       io/src/DSWriter.cc
       io/src/TrackCursor.cc
       io/src/TrackNav.cc
       util/src/ReadFile.cc
       $<TARGET_OBJECTS:stlplus>
       $<TARGET_OBJECTS:RATDict>)
target_link_libraries(RATEvent PUBLIC ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
target_include_directories(RATEvent PUBLIC ${RAT_INCDIRS})
### Target: Custom ROOT which automatically loads rootinit.C from $RATROOT
add_executable(root root.cc)
target_link_libraries(root PUBLIC ${ROOT_LIBRARIES} Threads::Threads)
add_dependencies(root RATEvent)

#### Target: GEANT4 neutron capture data for Gd
# TODO
#installdata = env.Command('installdata', '#data/neutron/load_data.csh',
#'csh data/neutron/load_data.csh')

install(TARGETS rat root RATPAC RATEvent
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES rootinit.C
       DESTINATION src)

### Install the headers
install(DIRECTORY ${RAT_INCDIRS} DESTINATION ${CMAKE_INSTALL_PREFIX})
