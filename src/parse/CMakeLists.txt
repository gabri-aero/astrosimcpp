set(CPP_SOURCES 
    TLE.cpp
    TLEParser.cpp)

set(HPP_HEADERS 
    TLE.hpp
    TLEParser.hpp)

target_sources(${CPP_TARGET} PRIVATE  ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Time included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()