set(CPP_SOURCES)
set(HPP_HEADERS Spice.hpp)
target_sources(${CPP_TARGET} PRIVATE  ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Propagator included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()