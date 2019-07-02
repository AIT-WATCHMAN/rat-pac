add_executable(bonsai bonsai.cc)
target_link_libraries(bonsai PUBLIC ${ROOT_LIBRARIES} RATEvent RATPAC)
target_include_directories(bonsai PUBLIC ${RAT_INCDIRS})