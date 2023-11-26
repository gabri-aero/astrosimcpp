target_include_directories(${CPP_TARGET}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/
)

add_subdirectory(bodies)
add_subdirectory(accelerations)
add_subdirectory(propagator)
add_subdirectory(math)
add_subdirectory(numerical)
add_subdirectory(orbit)
add_subdirectory(time)
add_subdirectory(parse)
add_subdirectory(frames)
