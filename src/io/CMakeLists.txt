###########################################################
# CMakeLists for io module

add_library(io STATIC
        src/DSReader.cc
        src/DSWriter.cc
        src/InNetProducer.cc
        src/InROOTProducer.cc
        src/OutNetProc.cc
        src/OutROOTProc.cc
        src/TrackCursor.cc
        src/TrackNav.cc)

# Set our include directories
target_include_directories(io PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include)

# Link necessary dependencies
target_link_libraries(io PUBLIC cmd core db ds stlplus util)

# Copy our headers when installing
file(COPY include/ DESTINATION ${RATPAC_INCDIR})
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/RAT
        DESTINATION include)
