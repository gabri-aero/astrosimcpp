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

# Check if the current project is the master project
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(BUILD_TESTING ON)
else()
    set(BUILD_TESTING OFF)
endif()

set(DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)
add_definitions(-DDATA_DIR="${DATA_DIR}")

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

# Find cURL
find_package(CURL REQUIRED)

if (CURL_FOUND)
    message(STATUS "cURL found")
else()
    message(FATAL_ERROR "cURL not found. Please install libcurl4-openssl-dev")
endif()
target_link_libraries(${CPP_TARGET} curl)

# External libs directory
set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)

# Download CSpice
set(CSPICE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/cspice)

if (IS_DIRECTORY "${CSPICE_DIR}")
    message(STATUS "Directory ${CSPICE_DIR} exists")
else()
    message(STATUS "Directory ${CSPICE_DIR} does not exist")
    message(STATUS "CSpice will be downloaded and set up")
    # Setup CSpice
    if (IS_DIRECTORY ${EXTERNAL_DIR})
        message(STATUS "Directory ${EXTERNAL_DIR} exists")
    else()
        message(STATUS "Directory ${EXTERNAL_DIR} does not exist. It will be created.")
        file(MAKE_DIRECTORY ${EXTERNAL_DIR})
    endif()
    message(STATUS "Downloading CSpice files from https://naif.jpl.nasa.gov/pub/naif/toolkit")
    # Linux 64-bit version only
    file(DOWNLOAD 
        "https://naif.jpl.nasa.gov/pub/naif/toolkit//C/PC_Linux_GCC_64bit/packages/cspice.tar.Z" 
        "${EXTERNAL_DIR}/cspice.tar.Z")
    file(DOWNLOAD 
        "https://naif.jpl.nasa.gov/pub/naif/toolkit//C/PC_Linux_GCC_64bit/packages/importCSpice.csh"
        "${EXTERNAL_DIR}/importCSpice.csh")
    message(STATUS "CSpice files downloaded successfully")
    # Run importCSpice.csh
    execute_process(
        COMMAND csh -f importCSpice.csh
        WORKING_DIRECTORY ${EXTERNAL_DIR}
        OUTPUT_QUIET
    )
    # Remove unnecessary files
    execute_process(
        COMMAND rm -rf importCSpice.csh cspice.tar
        WORKING_DIRECTORY ${EXTERNAL_DIR}
    )
    if(IS_DIRECTORY ${CSPICE_DIR})
        message(STATUS "CSpice built successfully")
    else()
        message(FATAL_ERROR "CSpice built failed")
    endif()
endif()

# Link CSpice
find_library(CSPICE_LIBRARY
             NAMES cspice.a
             PATHS external/cspice/lib)
if (CSPICE_LIBRARY)
    message(STATUS "Found the library: ${CSPICE_LIBRARY}")
    target_link_libraries(${CPP_TARGET} ${CSPICE_LIBRARY})
    include_directories(external/cspice/include)
else()
    message(FATAL_ERROR "Could not find the CSpice.")
endif()

# Download basic planetary ephemeris kernels
set(KERNELS_DIR ${DATA_DIR}/kernels)
set(DE440_FILE ${KERNELS_DIR}/de440.bsp)
set(PCK_FILE ${KERNELS_DIR}/pck00011.tpc)
set(GM_DE440_FILE ${KERNELS_DIR}/gm_de440.tpc)

if (IS_DIRECTORY ${KERNELS_DIR})
    message(STATUS "Directory ${KERNELS_DIR} exists")
else()
    message(STATUS "Directory ${KERNELS_DIR} does not exist. It will be created.")
    file(MAKE_DIRECTORY ${KERNELS_DIR})
endif()

if (EXISTS ${DE440_FILE})
    message(STATUS "DE440 ephemeris file already available")
else()
    message(STATUS "DE440 ephemeris not available")
    message(STATUS "Downloading DE440 file")
    execute_process(
        COMMAND wget --progress=dot:mega "https://naif.jpl.nasa.gov/pub/naif/generic_kernels/spk/planets/de440.bsp"
        WORKING_DIRECTORY ${KERNELS_DIR}
        RESULT_VARIABLE result
    )
    message(STATUS "de440.bsp file downloaded successfully")
endif()

if (EXISTS ${GM_DE440_FILE})
    message(STATUS "DE440 GM file already available")
else()
    message(STATUS "DE440 GM file not available")
    message(STATUS "Downloading DE440 GM file")
    execute_process(
        COMMAND wget -q "https://naif.jpl.nasa.gov/pub/naif/generic_kernels/pck/gm_de440.tpc"
        WORKING_DIRECTORY ${KERNELS_DIR}
        RESULT_VARIABLE result
    )
    message(STATUS "gm_de440.tpc file downloaded successfully")
endif()

if (EXISTS ${PCK_FILE})
    message(STATUS "PCK00011 file already available")
else()
    message(STATUS "PCK00011 file not available")
    message(STATUS "Downloading PCK00111 file")
    execute_process(
        COMMAND wget -q "https://naif.jpl.nasa.gov/pub/naif/generic_kernels/pck/pck00011.tpc"
        WORKING_DIRECTORY ${KERNELS_DIR}
        RESULT_VARIABLE result
    )
    message(STATUS "pck00011.tpc file downloaded successfully")
endif()

add_definitions(-DSPICE_KERNELS_DIR="${KERNELS_DIR}")


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