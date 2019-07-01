add_library(fit OBJECT
        src/FitPathProc.cc
        src/FitCentroidProc.cc
        src/FitBonsaiProc.cc
        src/MiniSim.cc)


target_include_directories(fit PRIVATE
        ${PROJECT_SOURCE_DIR}/src/cmd/include
        ${PROJECT_SOURCE_DIR}/src/core/include
        ${PROJECT_SOURCE_DIR}/src/daq/include
        ${PROJECT_SOURCE_DIR}/src/db/include
        ${PROJECT_SOURCE_DIR}/src/ds/include
        ${PROJECT_SOURCE_DIR}/src/gen/include
        ${PROJECT_SOURCE_DIR}/src/gen/include
        ${PROJECT_SOURCE_DIR}/src/geo/include
        ${PROJECT_SOURCE_DIR}/src/io/include
        ${PROJECT_SOURCE_DIR}/src/physics/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include
        ${PROJECT_SOURCE_DIR}/src/util/include)
target_include_directories(fit PRIVATE include)

install(DIRECTORY include # source directory
        DESTINATION include/${PROJECT_NAME} # target directory
        FILES_MATCHING PATTERN "*.hh")

install(DIRECTORY bonsai # source directory
        DESTINATION include/${PROJECT_NAME}/BONSAI # target directory
        FILES_MATCHING PATTERN "*.h"
        FILES_MATCHING PATTERN "*.inline")
