add_library(fit STATIC
        src/FitPathProc.cc
        src/FitCentroidProc.cc
        src/FitBonsaiProc.cc
        src/MiniSim.cc)


target_include_directories(fit PRIVATE
        ${PROJECT_SOURCE_DIR}/src/core/include
        ${PROJECT_SOURCE_DIR}/src/db/include
        ${PROJECT_SOURCE_DIR}/src/ds/include
        ${PROJECT_SOURCE_DIR}/src/physics/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include
        ${PROJECT_SOURCE_DIR}/src/util/include)
target_include_directories(fit PRIVATE include)
target_link_libraries(fit PUBLIC ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})

add_library(bonsai STATIC
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
        bonsai/plato.cc
        bonsai/pmt_geometry.cc
        bonsai/pot.cc
        bonsai/searchgrid.cc
        bonsai/timefit.cc
        bonsai/tree.cc
        bonsai/vertex.cc
        bonsai/vertexfit.cc)
target_include_directories(bonsai PRIVATE include)
target_link_libraries(bonsai PUBLIC ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})

# TODO
add_library(bonsai_fortran OBJECT
        bonsai/lfariadne.F)
set_property(TARGET bonsai_fortran PROPERTY LINKER_LANGUAGE Fortran)
