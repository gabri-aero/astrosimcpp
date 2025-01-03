#include "BaseFrame.hpp"

math::matrix BaseFrame::from(const BaseFrame& from_frame, const Epoch& epoch) const {
    return get_dcm(epoch).T()*from_frame.get_dcm(epoch);
}
    
math::matrix BaseFrame::to(const BaseFrame& to_frame, const Epoch& epoch) const {
    return to_frame.get_dcm(epoch).T()* get_dcm(epoch);
};