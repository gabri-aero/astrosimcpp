set(HPP_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Gravity.hpp)
set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Gravity.cpp)
target_sources(${CPP_TARGET} PRIVATE ${HPP_HEADERS} ${CPP_SOURCES})

message(STATUS "Accelerations included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()