add_library(core OBJECT
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

target_include_directories(core PUBLIC ${RAT_INCDIRS})
