set(CPP_SOURCES 
    FrameUtils.cpp
    BodyFixed.cpp
    EOP.cpp
    IAU2000.cpp
    InertialFrame.cpp
    BaseFrame.cpp)
set(HPP_HEADERS 
    BaseFrame.hpp
    FrameUtils.hpp
    BodyFixed.hpp
    EOP.hpp
    IAU2000.hpp
    InertialFrame.hpp)
target_sources(${CPP_TARGET} PRIVATE  ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Frames included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()