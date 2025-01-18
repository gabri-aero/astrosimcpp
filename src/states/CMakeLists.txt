set(CPP_SOURCES 
    Keplerian.cpp 
    Cartesian.cpp
    OrbitUtils.cpp
    Trajectory.cpp)

set(HPP_HEADERS 
    BaseState.hpp
    Keplerian.hpp 
    Cartesian.hpp
    OrbitUtils.hpp
    Trajectory.hpp)

target_sources(${CPP_TARGET} PRIVATE  ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Orbit included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()