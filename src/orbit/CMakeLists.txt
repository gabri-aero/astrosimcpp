set(CPP_SOURCES 
    Orbit.cpp 
    StateVector.cpp
    OrbitUtils.cpp)

set(HPP_HEADERS 
    Orbit.hpp 
    StateVector.hpp
    OrbitUtils.hpp)

target_sources(${CPP_TARGET} PRIVATE  ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Orbit included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()