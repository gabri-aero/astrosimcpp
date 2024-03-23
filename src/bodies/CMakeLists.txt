set(CPP_SOURCES 
    Body.cpp
    NaturalBody.cpp
    )
set(HPP_HEADERS
    Body.hpp
    NaturalBody.hpp)
target_sources(${CPP_TARGET} PRIVATE ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Bodies included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()