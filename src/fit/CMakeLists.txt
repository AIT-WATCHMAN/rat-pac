add_library(fit OBJECT
        src/FitPathProc.cc
        src/FitCentroidProc.cc
        src/FitBonsaiProc.cc
        src/MiniSim.cc)

target_include_directories(fit PUBLIC ${RAT_INCDIRS})

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
target_include_directories(_bonsai PUBLIC include)
