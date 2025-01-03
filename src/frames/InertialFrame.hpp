#ifndef _INERTIAL_FRAME_HPP_
#define _INERTIAL_FRAME_HPP_

#include <math/Vector.hpp>
#include <math/Matrix.hpp>
#include <frames/IAU2000.hpp>
#include <frames/BaseFrame.hpp>

/**
 * This class defines any purely inertial frame w.r.t. to the ICRF (International Celestial Reference Frame).
 * + The orientation of the frame at hand is given by a constant rotation matrix at any time. 
 * + The origin w.r.t. the ICRS is assumed to be constant at any time (typically the origin is the same)
 */
class InertialFrame : public BaseFrame {
protected:
    math::vector origin;
    math::matrix dcm; // Direction Cosine Matrix in the ICRS
public:
    InertialFrame(math::matrix dcm=math::matrix::eye(3), math::vector origin={0,0,0});
    using BaseFrame::from;
    using BaseFrame::to;
    math::matrix from(const InertialFrame& from_frame) const;
    math::matrix to(const InertialFrame& to_frame) const;
    math::matrix get_dcm(const Epoch& epoch = Epoch(0)) const override final;
};

// Pre-defined inertial frames
extern InertialFrame ICRF; // International Celestial Reference Frame
extern InertialFrame GCRF; // Assumed that GCRF=ICRF
extern InertialFrame EME2000; // EME2000 (also dynamic J2000) is deviated from GCRS by the frame bias matrix

/**
 * This class defines an inertial frame w.r.t. to the ICRF as determined by the Mean Equator of Date
 */
class MOD : public InertialFrame {
public:
    MOD(Epoch epoch);
};

/**
 * This class defines an inertial frame w.r.t. to the ICRF as determined by the Mean Ecliptic of Date
 */
class EOD : public MOD {
public:
    EOD(Epoch epoch);
};

#endif //_INERTIAL_FRAME_HPP_