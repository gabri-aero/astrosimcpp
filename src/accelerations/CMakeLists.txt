set(HPP_HEADERS
    Gravity.hpp
    Atmosphere.hpp)
set(CPP_SOURCES
    Gravity.cpp)
target_sources(${CPP_TARGET} PRIVATE ${HPP_HEADERS} ${CPP_SOURCES})

message(STATUS "Accelerations included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()