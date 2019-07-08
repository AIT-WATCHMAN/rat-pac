###########################################################
# CMakeLists for ds module

add_library(ds STATIC
        src/Root.cc
        src/MCPMT.cc
        src/RunStore.cc)
# Set our include directories
target_include_directories(ds PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
$<INSTALL_INTERFACE:include)

# Link necessary dependencies
target_link_libraries(ds PUBLIC core db geo stlplus util)

# Copy our headers when installing
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/RAT
DESTINATION include)

#################################################
# Create Root Dictionary

# Have to global import to work with root macro
include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${PROJECT_SOURCE_DIR}/src/io/include
        ${PROJECT_SOURCE_DIR}/src/db/include
        ${PROJECT_SOURCE_DIR}/src/core/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include
        ${PROJECT_SOURCE_DIR}/src/util/include)

root_generate_dictionary(G__RATDict
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/Root.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/EV.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/MC.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/MCParticle.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/MCPhoton.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/MCPMT.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/MCSummary.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/PMT.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/RunStore.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/Run.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/PosFit.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/PMTInfo.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/MCTrack.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/MCTrackStep.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/Calib.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/Centroid.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/PathFit.hh
        ${CMAKE_CURRENT_LIST_DIR}/include/RAT/DS/BonsaiFit.hh
        ${PROJECT_SOURCE_DIR}/src/io/include/RAT/DSReader.hh
        ${PROJECT_SOURCE_DIR}/src/io/include/RAT/DSWriter.hh
        ${PROJECT_SOURCE_DIR}/src/io/include/RAT/TrackNav.hh
        ${PROJECT_SOURCE_DIR}/src/io/include/RAT/TrackNode.hh
        ${PROJECT_SOURCE_DIR}/src/io/include/RAT/TrackCursor.hh
        ${PROJECT_SOURCE_DIR}/src/db/include/RAT/DB.hh
        ${PROJECT_SOURCE_DIR}/src/db/include/RAT/DBLink.hh
        ${PROJECT_SOURCE_DIR}/src/db/include/RAT/DBTextLoader.hh
        ${PROJECT_SOURCE_DIR}/src/db/include/RAT/DBJsonLoader.hh
        ${PROJECT_SOURCE_DIR}/src/db/include/RAT/HTTPDownloader.hh
        ${PROJECT_SOURCE_DIR}/src/core/include/RAT/Log.hh
        ${PROJECT_SOURCE_DIR}/src/io/include/RAT/ObjInt.hh
        ${PROJECT_SOURCE_DIR}/src/io/include/RAT/ObjDbl.hh
        LINKDEF include/RAT/DS/LinkDef.hh
        DEPENDENCIES io db core stlplus util ds)

add_library(RATDict OBJECT G__RATDict.cxx)
target_include_directories(RATDict PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_link_libraries(RATDict PUBLIC core db io)

# Export the proper dicitonary files to lib
file(COPY include/ DESTINATION ${RATPAC_INCDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libRATDict_rdict.pcm 
              ${CMAKE_CURRENT_BINARY_DIR}/libRATDict.rootmap
       DESTINATION lib)
