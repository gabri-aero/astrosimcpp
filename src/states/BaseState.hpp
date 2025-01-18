#ifndef _BASE_STATE_HPP_
#define _BASE_STATE_HPP_

#include <math/Vector.hpp>

class BaseState : public math::vector {
public:
    using math::vector::vector; // Inherit math::vector constructors
};


#endif // _BASE_STATE_HPP_