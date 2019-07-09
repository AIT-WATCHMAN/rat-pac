###########################################################
# CMakeLists for daq module

add_library(daq OBJECT
        src/LessSimpleDAQProc.cc
        src/MiniCleanPMTCharge.cc
        src/PDFPMTCharge.cc
        src/LessSimpleDAQ2Proc.cc
        src/PDFPMTTime.cc
        src/SimpleDAQProc.cc)

# Set our include directories
target_include_directories(daq PUBLIC
        $<BUILD_INTERFACE:${RATPAC_INCDIR}>
        $<INSTALL_INTERFACE:include)

# # Link necessary dependencies
# target_link_libraries(daq PUBLIC core db ds geo stlplus util)

# Copy our headers when installing
file(COPY include/ DESTINATION ${RATPAC_INCDIR})
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/RAT
        DESTINATION include)