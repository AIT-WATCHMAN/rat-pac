add_library(physics OBJECT
        src/BNLOpWLS.cc
        src/BNLOpWLSBuilder.cc
        src/BNLOpWLSData.cc
        src/Dicebox158Gd.cc
        src/G4OpWLSBuilder.cc
        src/GLG4OpAttenuation.cc
        src/GLG4PMTOpticalModel.cc
        src/GLG4Scint.cc
        src/PhotonThinning.cc
        src/PhysicsList.cc)

target_include_directories(physics PRIVATE
        ${PROJECT_SOURCE_DIR}/src/core/include
        ${PROJECT_SOURCE_DIR}/src/daq/include
        ${PROJECT_SOURCE_DIR}/src/db/include
        ${PROJECT_SOURCE_DIR}/src/ds/include
        ${PROJECT_SOURCE_DIR}/src/fit/include
        ${PROJECT_SOURCE_DIR}/src/gen/include
        ${PROJECT_SOURCE_DIR}/src/gen/include
        ${PROJECT_SOURCE_DIR}/src/geo/include
        ${PROJECT_SOURCE_DIR}/src/io/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include
        ${PROJECT_SOURCE_DIR}/src/util/include)
target_include_directories(physics PRIVATE include)

install(DIRECTORY include # source directory
        DESTINATION include/${PROJECT_NAME} # target directory
        FILES_MATCHING PATTERN "*.hh")
