set(CPP_SOURCES 
    Body.cpp
    NaturalBody.cpp
    EphemerisBody.cpp
    Spacecraft.cpp
    )
set(HPP_HEADERS
    Body.hpp
    NaturalBody.hpp
    EphemerisBody.hpp
    Spacecraft.hpp
    )
target_sources(${CPP_TARGET} PRIVATE ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Bodies included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()