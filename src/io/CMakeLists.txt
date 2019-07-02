add_library(io OBJECT
        src/DSReader.cc
        src/DSWriter.cc
        src/InNetProducer.cc
        src/InROOTProducer.cc
        src/OutNetProc.cc
        src/OutROOTProc.cc
        src/TrackCursor.cc
        src/TrackNav.cc)

target_include_directories(io PUBLIC ${RAT_INCDIRS})
