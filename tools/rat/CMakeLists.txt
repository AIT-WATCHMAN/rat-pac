############################################################
# CMakeLists for rat tool

add_executable(rat rat.cc)
target_link_libraries(rat PRIVATE ${ROOT_LIBRARIES} RATEvent RATPAC)
set_target_properties(rat
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

install(TARGETS rat
        RUNTIME DESTINATION bin)