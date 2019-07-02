add_executable(visualizer visualizer.cc)
target_link_libraries(visualizer PUBLIC ${ROOT_LIBRARIES} RATEvent RATPAC)
target_include_directories(visualizer PUBLIC ${RAT_INCDIRS})