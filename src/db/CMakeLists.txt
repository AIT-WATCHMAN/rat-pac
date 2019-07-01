add_library(db OBJECT
        src/DBTextLoader.cc
        src/HTTPDownloader.cc
        src/json.cc
        src/DBLink.cc
        src/DB.cc
        src/DBJsonLoader.cc
        src/DBTable.cc)


target_include_directories(db PRIVATE
        ${PROJECT_SOURCE_DIR}/src/cmd/include
        ${PROJECT_SOURCE_DIR}/src/core/include
        ${PROJECT_SOURCE_DIR}/src/daq/include
        ${PROJECT_SOURCE_DIR}/src/ds/include
        ${PROJECT_SOURCE_DIR}/src/fit/include
        ${PROJECT_SOURCE_DIR}/src/gen/include
        ${PROJECT_SOURCE_DIR}/src/gen/include
        ${PROJECT_SOURCE_DIR}/src/geo/include
        ${PROJECT_SOURCE_DIR}/src/io/include
        ${PROJECT_SOURCE_DIR}/src/physics/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include
        ${PROJECT_SOURCE_DIR}/src/util/include)
target_include_directories(db PRIVATE include)

install(DIRECTORY include # source directory
        DESTINATION include/${PROJECT_NAME} # target directory
        FILES_MATCHING PATTERN "*.hh")
