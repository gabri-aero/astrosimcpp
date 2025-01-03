#ifndef _BASE_FRAME_HPP_
#define _BASE_FRAME_HPP_

#include<math/Matrix.hpp>
#include<time/Epoch.hpp>

class BaseFrame {
public:
    virtual math::matrix get_dcm(const Epoch& epoch) const = 0;
    math::matrix from(const BaseFrame& from_frame, const Epoch& epoch) const;
    math::matrix to(const BaseFrame& to_frame, const Epoch& epoch) const;
};

#endif //_BASE_FRAME_HPP_