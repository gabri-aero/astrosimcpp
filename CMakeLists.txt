cmake_minimum_required(VERSION 3.22.1)

project(astrosim
  VERSION 0.0.1
  DESCRIPTION "A library for astrodynamics simulations"
)

add_compile_options(-std=c++17)
add_compile_options(-Wno-terminate)
add_compile_options(-Wno-return-type)

set(CPP_TARGET astrosim)
add_library(astrosim SHARED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE  # Set this option to ensure proper handling of timestamps
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
function(download_kernel FILE WEB_PATH)
    set(KERNEL_PATH ${KERNELS_DIR}/${FILE})
    
    if (EXISTS ${KERNEL_PATH})
        message(STATUS "SPICE kernel file ${FILE} already available")
    else()
        message(STATUS "Downloading ${FILE}")
        execute_process(
            COMMAND wget -q ${WEB_PATH}
            WORKING_DIRECTORY ${KERNELS_DIR}
            RESULT_VARIABLE result
        )
        message(STATUS "${FILE} downloaded successfully")
    endif()
endfunction()

set(KERNELS_DIR ${DATA_DIR}/kernels)

if (IS_DIRECTORY ${KERNELS_DIR})
    message(STATUS "Directory ${KERNELS_DIR} exists")
else()
    message(STATUS "Directory ${KERNELS_DIR} does not exist. It will be created.")
    file(MAKE_DIRECTORY ${KERNELS_DIR})
endif()

download_kernel(de440.bsp "https://naif.jpl.nasa.gov/pub/naif/generic_kernels/spk/planets/de440.bsp")
download_kernel(gm_de440.tpc "https://naif.jpl.nasa.gov/pub/naif/generic_kernels/pck/gm_de440.tpc")
download_kernel(pck00011.tpc "https://naif.jpl.nasa.gov/pub/naif/generic_kernels/pck/pck00011.tpc")
download_kernel(naif0012.tls "https://naif.jpl.nasa.gov/pub/naif/generic_kernels/lsk/naif0012.tls")

add_definitions(-DSPICE_KERNELS_DIR="${KERNELS_DIR}")

set(GRAVITY_DIR ${DATA_DIR}/gravity)

# Add gravity potential default data
function(download_gravity_file FILE WEB_PATH)
set(FILE_PATH ${GRAVITY_DIR}/${FILE})

if (IS_DIRECTORY ${GRAVITY_DIR})
    message(STATUS "Directory ${GRAVITY_DIR} exists")
else()
    message(STATUS "Directory ${GRAVITY_DIR} does not exist. It will be created.")
    file(MAKE_DIRECTORY ${GRAVITY_DIR})
endif()

if (EXISTS ${FILE_PATH})
    message(STATUS "Gravity data file ${FILE} already available")
else()
    message(STATUS "Downloading ${FILE}")
    execute_process(
        COMMAND wget -q ${WEB_PATH}
        WORKING_DIRECTORY ${GRAVITY_DIR}
        RESULT_VARIABLE result
    )
    message(STATUS "${FILE} downloaded successfully")
endif()
endfunction()

# Download planetary gravity data from NASA PDS
download_gravity_file(jgmess_160a_sha.tab "https://pds-geosciences.wustl.edu/messenger/mess-h-rss_mla-5-sdp-v1/messrs_1001/data/shadr/jgmess_160a_sha.tab")
download_gravity_file(jggrx_0420a_sha.tab "https://pds-geosciences.wustl.edu/grail/grail-l-lgrs-5-rdr-v1/grail_1001/shadr/jggrx_0420a_sha.tab")
download_gravity_file(jgmro_120f_sha.tab "https://pds-geosciences.wustl.edu/mro/mro-m-rss-5-sdp-v1/mrors_1xxx/data/shadr/jgmro_120f_sha.tab")
download_gravity_file(shgj180u.a01 "https://pds-geosciences.wustl.edu/mgn/mgn-v-rss-5-gravity-l2-v1/mg_5201/gravity/shgj180u.a01")

# Download some Earth gravity field models coefficients (GFC) from ICGEM
download_gravity_file(EGM2008.gfc "https://icgem.gfz-potsdam.de/getmodel/gfc/c50128797a9cb62e936337c890e4425f03f0461d7329b09a8cc8561504465340/EGM2008.gfc")

# Download IERS file
function(download_iers_file FILE WEB_PATH)
set(FILE_PATH ${IERS_DIR}/${FILE})

if (IS_DIRECTORY ${IERS_DIR})
    message(STATUS "Directory ${IERS_DIR} exists")
else()
    message(STATUS "Directory ${IERS_DIR} does not exist. It will be created.")
    file(MAKE_DIRECTORY ${IERS_DIR})
endif()

if (EXISTS ${FILE_PATH})
    message(STATUS "IERS data file ${FILE} already available")
else()
    message(STATUS "Downloading ${FILE}")
    execute_process(
        COMMAND wget -q ${WEB_PATH}
        WORKING_DIRECTORY ${IERS_DIR}
        RESULT_VARIABLE result
    )
    message(STATUS "${FILE} downloaded successfully")
endif()
endfunction()

set(IERS_DIR ${DATA_DIR}/iers)

download_iers_file(Leap_Second.dat "https://hpiers.obspm.fr/iers/bul/bulc/Leap_Second.dat")
download_iers_file(eopc04_14_IAU2000.62-now.txt "https://datacenter.iers.org/data/224/eopc04_14_IAU2000.62-now.txt")


download_iers_file(tab5.2a.txt "https://iers-conventions.obspm.fr/content/chapter5/additional_info/tab5.2a.txt")
download_iers_file(tab5.2b.txt "https://iers-conventions.obspm.fr/content/chapter5/additional_info/tab5.2b.txt")
download_iers_file(tab5.2d.txt "https://iers-conventions.obspm.fr/content/chapter5/additional_info/tab5.2d.txt")

download_iers_file(tab5.3a.txt "https://iers-conventions.obspm.fr/content/chapter5/additional_info/tab5.3a.txt")
download_iers_file(tab5.3b.txt "https://iers-conventions.obspm.fr/content/chapter5/additional_info/tab5.3b.txt")

add_definitions(-DGRAVITY_DIR="${GRAVITY_DIR}")
add_definitions(-DIERS_DIR="${IERS_DIR}")

set (CMAKE_CXX_FLAGS "-fopenmp")

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