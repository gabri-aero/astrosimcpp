set(CPP_SOURCES 
    Epoch.cpp
    TimeUtils.cpp)

set(HPP_HEADERS 
    Epoch.hpp
    TimeUtils.hpp
    TimeSeries.hpp)

target_sources(${CPP_TARGET} PRIVATE  ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Time included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()