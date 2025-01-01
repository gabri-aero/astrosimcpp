set(CPP_SOURCES
    Utils.cpp)

set(HPP_HEADERS
    Vector.hpp 
    Matrix.hpp 
    Legendre.hpp 
    Utils.hpp 
    SphericalHarmonics.hpp
    Rotation.hpp
    Interpolation.hpp)
    
target_sources(${CPP_TARGET} PRIVATE  ${CPP_SOURCES} ${HPP_HEADERS})

message(STATUS "Utils included")

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()