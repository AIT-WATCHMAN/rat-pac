############################################################
# CMakeLists for the tools of ratpac

if(BONSAI)
        add_subdirectory(bonsai)
endif()
add_subdirectory(visualizer)
add_subdirectory(rat)
add_subdirectory(root)

set_target_properties(bonsai visualizer rat root
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${RATPAC_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${RATPAC_LIBRARY_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${RATPAC_LIBRARY_DIR})
