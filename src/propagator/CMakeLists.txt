set(CPP_SOURCES Propagator.cpp)
set(HPP_HEADERS Propagator.hpp)
target_sources(${CPP_TARGET} PRIVATE  ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Propagator included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()