# Astrosim

![Version](https://img.shields.io/badge/version-0.0.1-blue.svg)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/gabri-aero/astrosimcpp/blob/main/LICENSE)

> Astrodynamics C++ library where I am implementing my learnings in the field

## Table of contents
- [Features](#features)
- [Usage](#usage)
- [Example](#example)
- [TO DO](#to-do)
- [References](#references)

## Features
- N-body problem simulation
- Numerical integration methods: Euler, RK4, RK45
- Time handling since 1972: TAI, TT, GPST, UTC.
- TLE satellite data parsing from [Celestrak](www.celestrak.org).
- Conversion between cartesian, keplerian elements, spherical coordinates.
- Ground tracks can be retrieved with some effort using Earth Rotation Angle.
- Built-in mathematical operations

## Usage

> [!IMPORTANT]
> The library can only be used in a Linux environment.

1. Add the GitHub repository as a submodule to your project.
```
git submodule add https://github.com/gabri-aero/astrosimcpp
```

2. Link the library to your CMake project.

```
add_subdirectory(astrosimcpp)
target_link_libraries(_core PRIVATE astrosim) 
```

You could also build the library yourself.

1. Clone the GitHub repository
```
git clone https://github.com/gabri-aero/astrosimcpp
```

2. Build the library
```
cd astrosimcpp
mkdir build
cd build
cmake ..
```

> [!NOTE]
> Direct installation is not yet supported.

## Example

An example to conduct a three body simulation is provided.

```cpp
// Import necessary header files
#include <bodies/Body.hpp>
#include <propagator/Propagator.hpp>

// Define bodies
double au = 1.49e11;
Body sun("SUN", 1.989e30, {0, 0, 0, 0, 0, 0});
Body earth("EARTH", 5.972e24, {au, 0, 0, 0, sqrt(sun.get_mu()/au), 0});
Body mars("MARS", 6.419e23, {1.52*au, 0, 0, 0, sqrt(sun.get_mu()/(1.52*au)), 0});

// Create propagation start and end epochs
Epoch start(2024, 1, 1, 0, 0, 0);
Epoch end(2025, 1, 1, 0, 0, 0);

// Create propagator
Propagator propagator(start, end);

// Add bodies to the propagator
propagator.add_bodies(sun, earth, mars);

// Create integrator
double day = 3600;
auto integrator = std::make_shared<RK4>(1*day);

// Add integrator to propagator
propagator.set_integrator(integrator);

// Run simulation
propagator.run();

// Retrieve bodies trajectories
auto sun_trajectory = sun.get_trajectory();
auto mars_trajectory = mars.get_trajectory();
auto earth_trajectory = earth.get_trajectory();
```

## TO DO

The following features are intended to be added in upcoming versions:
- Planetary ephemeris
- Body child classes to handle satellites and natural bodies
- Maneuvers
- Event handling
- Orbital perturbations
- UT1 time

## References

1. D. A. Vallado, “Fundamentals of Astrodynamics and Applications,” 2013.

2. O. Montenbruck and E. Gill, Satellite Orbits. Springer Berlin Heidelberg, 2000.

3. H. D. Curtis, Orbital Mechanics for Engineering Students. 2010.

4. IAU SOFA - Standards of Fundamental Astronomy: https://iausofa.org/

5. International Earth Rotation and Reference Systems Service: https://www.iers.org/