############################################################
# CMakeLists for rat tool

add_executable(rat rat.cc)
target_link_libraries(rat PRIVATE ${ROOT_LIBRARIES} RATEvent RATPAC)

install(TARGETS rat
        RUNTIME DESTINATION bin)