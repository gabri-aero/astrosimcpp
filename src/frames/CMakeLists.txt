set(CPP_SOURCES 
    FrameUtils.cpp)
set(HPP_HEADERS 
    FrameUtils.hpp)
target_sources(${CPP_TARGET} PRIVATE  ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Frames included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()