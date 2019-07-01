add_library(db OBJECT
        src/DBTextLoader.cc
        src/HTTPDownloader.cc
        src/json.cc
        src/DBLink.cc
        src/DB.cc
        src/DBJsonLoader.cc
        src/DBTable.cc)


target_include_directories(db PRIVATE
        ${PROJECT_SOURCE_DIR}/src/core/include
        ${PROJECT_SOURCE_DIR}/src/ds/include
        ${PROJECT_SOURCE_DIR}/src/stlplus/include
        ${PROJECT_SOURCE_DIR}/src/util/include)
target_include_directories(db PRIVATE include)
