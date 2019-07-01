add_library(ds OBJECT
        src/Root.cc
        src/MCPMT.cc
        src/RunStore.cc)


target_include_directories(ds PRIVATE
        ${PROJECT_SOURCE_DIR}/src/cmd/include
        ${PROJECT_SOURCE_DIR}/src/core/include
        ${PROJECT_SOURCE_DIR}/src/daq/include
        ${PROJECT_SOURCE_DIR}/src/db/include
        ${PROJECT_SOURCE_DIR}/src/fit/include
        ${PROJECT_SOURCE_DIR}/src/gen/include
        ${PROJECT_SOURCE_DIR}/src/gen/include
        ${PROJECT_SOURCE_DIR}/src/geo/include
        ${PROJECT_SOURCE_DIR}/src/io/include
        ${PROJECT_SOURCE_DIR}/src/physics/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include
        ${PROJECT_SOURCE_DIR}/src/util/include)
target_include_directories(ds PRIVATE include)

install(DIRECTORY include # source directory
        DESTINATION include/${PROJECT_NAME}/DS # target directory
        FILES_MATCHING PATTERN "*.hh")
