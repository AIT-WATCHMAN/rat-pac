add_library(daq STATIC
        src/LessSimpleDAQProc.cc
        src/MiniCleanPMTCharge.cc
        src/PDFPMTCharge.cc
        src/LessSimpleDAQ2Proc.cc
        src/PDFPMTTime.cc
        src/SimpleDAQProc.cc)

target_include_directories(daq PRIVATE
        ${PROJECT_SOURCE_DIR}/src/cmd/include
        ${PROJECT_SOURCE_DIR}/src/core/include
        ${PROJECT_SOURCE_DIR}/src/db/include
        ${PROJECT_SOURCE_DIR}/src/ds/include
        ${PROJECT_SOURCE_DIR}/src/fit/include
        ${PROJECT_SOURCE_DIR}/src/gen/include
        ${PROJECT_SOURCE_DIR}/src/gen/include
        ${PROJECT_SOURCE_DIR}/src/geo/include
        ${PROJECT_SOURCE_DIR}/src/io/include
        ${PROJECT_SOURCE_DIR}/src/physics/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include
        ${PROJECT_SOURCE_DIR}/src/util/include)
target_include_directories(daq PRIVATE include)

install(DIRECTORY include # source directory
        DESTINATION include/${PROJECT_NAME} # target directory
        FILES_MATCHING PATTERN "*.hh")
