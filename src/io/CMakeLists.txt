add_library(io STATIC
        src/DSReader.cc
        src/DSWriter.cc
        src/InNetProducer.cc
        src/InROOTProducer.cc
        src/OutNetProc.cc
        src/OutROOTProc.cc
        src/TrackCursor.cc
        src/TrackNav.cc)

target_include_directories(io PRIVATE
        ${PROJECT_SOURCE_DIR}/src/core/include
        ${PROJECT_SOURCE_DIR}/src/db/include
        ${PROJECT_SOURCE_DIR}/src/ds/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include
        ${PROJECT_SOURCE_DIR}/src/util/include)
target_include_directories(io PRIVATE include)

target_link_libraries(io PUBLIC ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})
