###########################################################
# CMakeLists for fit module

add_library(fit OBJECT
        src/FitPathProc.cc
        src/FitCentroidProc.cc
        src/FitBonsaiProc.cc
        src/MiniSim.cc)


# Set our include directories
target_include_directories(fit PUBLIC
        $<BUILD_INTERFACE:${RATPAC_INCDIR}>
        $<INSTALL_INTERFACE:include)

# # Link necessary dependencies
# target_link_libraries(fit PUBLIC core db ds physics stlplus util)

# Copy our headers when installing
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/RAT
        DESTINATION include)

### Bonsai
add_library(_bonsai OBJECT
        bonsai/ariadne.cc
        bonsai/binfile.cc
        bonsai/bonsai.cc
        bonsai/bonsaifit.cc
        bonsai/bonsaimainpp.cc
        bonsai/bscalls.cc
        bonsai/centroid.cc
        bonsai/fit_param.cc
        bonsai/fourhitgrid.cc
        bonsai/goodness.cc
        bonsai/hits.cc
        bonsai/hitsel.cc
        bonsai/likelihood.cc
        bonsai/lfariadne.F
        bonsai/plato.cc
        bonsai/pmt_geometry.cc
        bonsai/pot.cc
        bonsai/searchgrid.cc
        bonsai/timefit.cc
        bonsai/tree.cc
        bonsai/vertex.cc
        bonsai/vertexfit.cc)

# Set our include directories
target_include_directories(_bonsai PUBLIC
        $<BUILD_INTERFACE:${RATPAC_INCDIR}>
        $<INSTALL_INTERFACE:include)

# Copy our headers when installing
file(COPY include/ DESTINATION ${RATPAC_INCDIR})
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/BONSAI
        DESTINATION include)
        
