###########################################################
# CMakeLists for util module

add_library(util STATIC
        src/GLG4StringUtil.cc
        src/GaussianRatioPDF.cc
        src/MultiChargeDist.cc
        src/PolygonOrientation.cc
        src/ReadFile.cc
        src/Sampling.cc
        src/SilenceRooFitBanner.cc
        src/SimpsIntegral.cc
        src/StringUtil.cc
        src/getopt.cc
        src/getopt1.cc)

# Set our include directories
target_include_directories(util PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include)

# Link necessary dependencies
target_link_libraries(util PUBLIC core daq db stlplus)

# Copy our headers when installing
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/RAT
        DESTINATION include)

#### Target: Shared library to make RooFit stop printing that stupid banner
add_library(SilenceRooFitBanner SHARED src/SilenceRooFitBanner.cc)
target_link_libraries(SilenceRooFitBanner PUBLIC ${ROOT_LIBRARIES})
install(TARGETS SilenceRooFitBanner
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)
