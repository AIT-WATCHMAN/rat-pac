add_library(daq OBJECT
        src/LessSimpleDAQProc.cc
        src/MiniCleanPMTCharge.cc
        src/PDFPMTCharge.cc
        src/LessSimpleDAQ2Proc.cc
        src/PDFPMTTime.cc
        src/SimpleDAQProc.cc)

target_include_directories(daq PUBLIC ${RAT_INCDIRS})
