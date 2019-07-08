############################################################
# CMakeLists for the tools of ratpac

if(BONSAI)
        add_subdirectory(bonsai)
endif()
add_subdirectory(visualizer)
add_subdirectory(rat)
add_subdirectory(root)
