add_library(ds STATIC
        src/Root.cc
        src/MCPMT.cc
        src/RunStore.cc)

target_include_directories(ds PUBLIC ${RAT_INCDIRS})

# Have to global import to work with root macro
include_directories(${RAT_INCDIRS})
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
        LINKDEF include/RAT/DS/LinkDef.hh)
add_library(RATDict OBJECT G__RATDict.cxx)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libRATDict_rdict.pcm ${CMAKE_CURRENT_BINARY_DIR}/libRATDict.rootmap
       PERMISSIONS OWNER_WRITE OWNER_READ
       GROUP_READ
       WORLD_READ
       DESTINATION lib)
