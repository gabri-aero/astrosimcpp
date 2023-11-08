set(CPP_SOURCES AstroEngine.cpp)
set(HPP_HEADERS AstroEngine.hpp)
target_sources(${CPP_TARGET} PRIVATE  ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Bodies included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()