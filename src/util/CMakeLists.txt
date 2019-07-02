add_library(util OBJECT
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

target_include_directories(util PUBLIC ${RAT_INCDIRS})

#### Target: Shared library to make RooFit stop printing that stupid banner
add_library(SilenceRooFitBanner SHARED src/SilenceRooFitBanner.cc)
target_link_libraries(SilenceRooFitBanner PUBLIC ${ROOT_LIBRARIES})
