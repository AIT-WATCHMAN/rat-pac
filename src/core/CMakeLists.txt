add_library(core STATIC
        src/GLG4HitPhoton.cc
        src/GLG4HitPMT.cc
        src/GLG4SteppingAction.cc
        src/PythonProc.cc
        src/ProcBlock.cc
        src/RunManager.cc
        src/CountProc.cc
        src/PruneProc.cc
        src/Gsim.cc
        src/ConstructUserProc.cc
        src/GLG4VisManager.cc
        src/GLG4VEventAction.cc
        src/StackingAction.cc
        src/Producer.cc
        src/Trajectory.cc
        src/Processor.cc
        src/SignalHandler.cc
        src/TrackInfo.cc
        src/Log.cc
        src/GLG4HitPMTCollection.cc)

target_include_directories(core PRIVATE
        ${PROJECT_SOURCE_DIR}/src/cmd/include
        ${PROJECT_SOURCE_DIR}/src/daq/include
        ${PROJECT_SOURCE_DIR}/src/db/include
        ${PROJECT_SOURCE_DIR}/src/ds/include
        ${PROJECT_SOURCE_DIR}/src/gen/include
        ${PROJECT_SOURCE_DIR}/src/geo/include
        ${PROJECT_SOURCE_DIR}/src/physics/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include
        ${PROJECT_SOURCE_DIR}/src/util/include)
target_include_directories(core PRIVATE include)
target_link_libraries(core PUBLIC ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})
