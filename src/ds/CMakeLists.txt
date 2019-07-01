add_library(ds STATIC
        src/Root.cc
        src/MCPMT.cc
        src/RunStore.cc)

target_include_directories(ds PRIVATE
        ${PROJECT_SOURCE_DIR}/src/core/include
        ${PROJECT_SOURCE_DIR}/src/db/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include
        ${PROJECT_SOURCE_DIR}/src/util/include)
target_include_directories(ds PRIVATE include)
target_link_libraries(ds PUBLIC ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})

