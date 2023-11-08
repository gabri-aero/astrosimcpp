set(CPP_SOURCES Euler.cpp RK4.cpp RK45.cpp)
set(HPP_HEADERS Euler.hpp RK4.hpp RK45.hpp BaseIntegrator.hpp)
target_sources(${CPP_TARGET} PRIVATE  ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Engine included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()