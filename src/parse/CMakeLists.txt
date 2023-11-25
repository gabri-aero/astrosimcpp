set(CPP_SOURCES )

set(HPP_HEADERS 
    TLEParser.hpp)

target_sources(${CPP_TARGET} PRIVATE  ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Time included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()