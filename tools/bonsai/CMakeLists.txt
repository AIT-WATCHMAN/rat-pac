############################################################
# CMakeLists for bonsai tool

add_executable(bonsai bonsai.cc)
target_link_libraries(bonsai PUBLIC RATPAC)
install(TARGETS bonsai
        RUNTIME DESTINATION bin)