add_library(daq OBJECT
        src/LessSimpleDAQProc.cc
        src/MiniCleanPMTCharge.cc
        src/PDFPMTCharge.cc
        src/LessSimpleDAQ2Proc.cc
        src/PDFPMTTime.cc
        src/SimpleDAQProc.cc)

target_include_directories(daq PRIVATE
        ${PROJECT_SOURCE_DIR}/src/core/include
        ${PROJECT_SOURCE_DIR}/src/db/include
        ${PROJECT_SOURCE_DIR}/src/ds/include
        ${PROJECT_SOURCE_DIR}/src/geo/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include
        ${PROJECT_SOURCE_DIR}/src/util/include)
target_include_directories(daq PRIVATE include)
