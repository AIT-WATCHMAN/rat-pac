
include_directories(${PROJECT_SOURCE_DIR}/include)

#add_subdirectory(cmd)
#add_subdirectory(core)
#add_subdirectory(daq)
add_subdirectory(db)
add_subdirectory(ds)
add_subdirectory(fit)
add_subdirectory(gen)
add_subdirectory(geo)
add_subdirectory(io)
add_subdirectory(physics)
add_subdirectory(stlplus)
add_subdirectory(util)


#add_library(RAT STATIC
#        $<TARGET_OBJECTS:cmd>
#        $<TARGET_OBJECTS:core>
#        $<TARGET_OBJECTS:daq>
#        $<TARGET_OBJECTS:db>
#        $<TARGET_OBJECTS:ds>
#        $<TARGET_OBJECTS:fit>
#        $<TARGET_OBJECTS:gen>
#        $<TARGET_OBJECTS:geo>
#        $<TARGET_OBJECTS:io>
#        $<TARGET_OBJECTS:physics>
#        $<TARGET_OBJECTS:stlplus>
#        $<TARGET_OBJECTS:util>)
#
#add_executable(rat rat.cc
#        $<TARGET_OBJECTS:cmd>
#        $<TARGET_OBJECTS:core>
#        $<TARGET_OBJECTS:daq>
#        $<TARGET_OBJECTS:db>
#        $<TARGET_OBJECTS:ds>
#        $<TARGET_OBJECTS:fit>
#        $<TARGET_OBJECTS:gen>
#        $<TARGET_OBJECTS:geo>
#        $<TARGET_OBJECTS:io>
#        $<TARGET_OBJECTS:physics>
#        $<TARGET_OBJECTS:stlplus>
#        $<TARGET_OBJECTS:util>)
#target_link_libraries(rat PUBLIC ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})
#
#
#
##### Target: Shared library for ROOT
#add_library(RATEvent SHARED
#        core/src/Log.cc
#        $<TARGET_OBJECTS:ds>
#        $<TARGET_OBJECTS:db>
#        io/src/DSReader.cc
#        io/src/DSWriter.cc
#        io/src/TrackCursor.cc
#        io/src/TrackNav.cc
#        util/src/ReadFile.cc
#        $<TARGET_OBJECTS:stlplus>)
#
##### Target: Shared library to make RooFit stop printing that stupid banner
#add_library(SilenceRooFitBanner SHARED util/src/SilenceRooFitBanner.cc)
#
##### Target: Custom ROOT which automatically loads rootinit.C from $RATROOT
#add_executable(root root.cc)
#target_link_libraries(root PRIVATE ${ROOT_LIBRARIES})

#### Target: GEANT4 neutron capture data for Gd
# TODO
#installdata = env.Command('installdata', '#data/neutron/load_data.csh',
#'csh data/neutron/load_data.csh')
