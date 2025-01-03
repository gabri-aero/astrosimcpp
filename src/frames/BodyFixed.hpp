#ifndef _BODY_FIXED_HPP_
#define _BODY_FIXED_HPP_

#include <math/Matrix.hpp>
#include <bodies/Body.hpp>
#include <time/Epoch.hpp>
#include <frames/BaseFrame.hpp>

class BodyFixed : public BaseFrame {
private:
    std::shared_ptr<Body> body;
public:
    BodyFixed(const Body& body);
    math::matrix get_dcm(const Epoch& epoch) const override final;
};

#endif //_BODY_FIXED_HPP_