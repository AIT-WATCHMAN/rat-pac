add_library(db OBJECT
        src/DBTextLoader.cc
        src/HTTPDownloader.cc
        src/json.cc
        src/DBLink.cc
        src/DB.cc
        src/DBJsonLoader.cc
        src/DBTable.cc)

target_include_directories(db PUBLIC ${RAT_INCDIRS})
