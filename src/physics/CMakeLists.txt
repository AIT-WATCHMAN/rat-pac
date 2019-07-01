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
        ${PROJECT_SOURCE_DIR}/src/cmd/include
        ${PROJECT_SOURCE_DIR}/src/core/include
        ${PROJECT_SOURCE_DIR}/src/db/include
        ${PROJECT_SOURCE_DIR}/src/ds/include
        ${PROJECT_SOURCE_DIR}/src/geo/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include
        ${PROJECT_SOURCE_DIR}/src/util/include)
target_include_directories(physics PRIVATE include)
