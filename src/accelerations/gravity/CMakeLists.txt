set(HPP_HEADERS
    Gravity.hpp
    SphericalHarmonics.hpp
    )
set(CPP_SOURCES
    Gravity.cpp
    SphericalHarmonics.cpp
    )
target_sources(${CPP_TARGET} PRIVATE ${HPP_HEADERS} ${CPP_SOURCES})

message(STATUS "Gravity included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()