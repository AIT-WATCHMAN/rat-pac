###########################################################
# CMakeLists for db module

add_library(db OBJECT
        src/DBTextLoader.cc
        src/HTTPDownloader.cc
        src/json.cc
        src/DBLink.cc
        src/DB.cc
        src/DBJsonLoader.cc
        src/DBTable.cc)

# Set our include directories
target_include_directories(db PUBLIC
        $<BUILD_INTERFACE:${RATPAC_INCDIR}>
        $<INSTALL_INTERFACE:include)

# # Link necessary dependencies
# target_link_libraries(db PUBLIC core ds geo stlplus util)

# Copy our headers when installing
file(COPY include/ DESTINATION ${RATPAC_INCDIR})
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/RAT
        DESTINATION include)
