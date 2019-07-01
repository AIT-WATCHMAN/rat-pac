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

target_include_directories(util PRIVATE
        ${PROJECT_SOURCE_DIR}/src/core/include
        ${PROJECT_SOURCE_DIR}/src/daq/include
        ${PROJECT_SOURCE_DIR}/src/db/include
#        ${PROJECT_SOURCE_DIR}/src/ds/include
#        ${PROJECT_SOURCE_DIR}/src/fit/include
#        ${PROJECT_SOURCE_DIR}/src/gen/include
#        ${PROJECT_SOURCE_DIR}/src/gen/include
#        ${PROJECT_SOURCE_DIR}/src/geo/include
#        ${PROJECT_SOURCE_DIR}/src/io/include
#        ${PROJECT_SOURCE_DIR}/src/physics/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include)
target_include_directories(util PRIVATE include)

install(DIRECTORY include # source directory
        DESTINATION include/${PROJECT_NAME} # target directory
        FILES_MATCHING PATTERN "*.hh")
