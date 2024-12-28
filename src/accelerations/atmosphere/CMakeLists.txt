set(HPP_HEADERS
    Atmosphere.hpp
    )
set(CPP_SOURCES
    )
target_sources(${CPP_TARGET} PRIVATE ${HPP_HEADERS} ${CPP_SOURCES})

message(STATUS "Atmosphere included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()