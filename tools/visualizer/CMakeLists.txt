############################################################
# CMakeLists for visualizer tool

add_executable(visualizer visualizer.cc)
target_link_libraries(visualizer PUBLIC ${ROOT_LIBRARIES} RATPAC)

install(TARGETS visualizer
        RUNTIME DESTINATION bin)