add_subdirectory(bonsai)
add_subdirectory(visualizer)

install(TARGETS bonsai visualizer
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)