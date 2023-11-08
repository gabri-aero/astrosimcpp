cmake_minimum_required(VERSION 3.22.1)

project(astrosim
  VERSION 0.0.1
  DESCRIPTION "A library for astrodynamics simulations"
)

set(CPP_TARGET astrosim)
add_library(astrosim SHARED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-std=c++17)
add_compile_options(-Wno-terminate)
add_compile_options(-Wno-return-type)

set(CMAKE_BUILD_TYPE Debug)

set(BUILD_TESTING ON)

# Google Test
if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

include_directories(external)

add_subdirectory(src)

set(ASTROSIMCPP_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}//src/accelerations/Gravity.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}//src/bodies/Body.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}//src/engine/AstroEngine.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}//src/engine/Orbit.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}//src/engine/StateVector.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math/Legendre.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math/Matrix.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math/Rotation.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math/SphericalHarmonics.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math/Utils.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math/Vector.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/numerical/BaseIntegrator.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/numerical/Euler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/numerical/RK4.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/numerical/RK45.hpp
)


target_include_directories(astrosim
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

install(
    TARGETS astrosim
    EXPORT AstrosimTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)

install(
    EXPORT AstrosimTargets
    FILE AstrosimTargets.cmake
    NAMESPACE Astrosim::
    DESTINATION lib/cmake/Astrosim
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "AstrosimConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

export(
    EXPORT AstrosimTargets
    FILE AstrosimTargets.cmake
    NAMESPACE Astrosim::
)