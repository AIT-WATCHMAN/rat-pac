###########################################################
# CMakeLists for physics module

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

# Set our include directories
target_include_directories(physics PUBLIC
        $<BUILD_INTERFACE:${RATPAC_INCDIR}>
        $<INSTALL_INTERFACE:include)

# # Link necessary dependencies
# target_link_libraries(physics PUBLIC cmd core db ds geo stlplus util)

# Copy our headers when installing
file(COPY include/ DESTINATION ${RATPAC_INCDIR})
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/RAT
        DESTINATION include)
