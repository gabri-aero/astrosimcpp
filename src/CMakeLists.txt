target_include_directories(${CPP_TARGET}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/
)

add_subdirectory(bodies)
add_subdirectory(accelerations)
add_subdirectory(engine)
add_subdirectory(math)
add_subdirectory(numerical)
add_subdirectory(orbit)