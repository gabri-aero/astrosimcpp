#include "InertialFrame.hpp"

InertialFrame::InertialFrame(math::matrix dcm, math::vector origin) 
: dcm(dcm), origin(origin) {

}

math::matrix InertialFrame::from(const InertialFrame& from_frame) const {
    return get_dcm().T()*from_frame.get_dcm();
}
    
math::matrix InertialFrame::to(const InertialFrame& to_frame) const {
    return to_frame.get_dcm().T()* get_dcm();
};

math::matrix InertialFrame::get_dcm(const Epoch& epoch) const {
    // Epoch plays no role, just for completeness
    return dcm;
}

InertialFrame ICRF;
InertialFrame GCRF;
InertialFrame EME2000;

MOD::MOD(Epoch epoch) {
    double t = epoch.with_reference_epoch(J2000).get_days() / 36525;
    double zeta = as2rad(2306.2181*t+0.30188*pow(t,2)+0.017998*pow(t,3));
    double theta = as2rad(2004.3109*t-0.42665*pow(t,2)-0.041833*pow(t,3));
    double z = as2rad(2306.2181*t+1.09468*pow(t,2)+0.018203*pow(t,3));
    
    InertialFrame(R3(zeta)*R2(-theta)*R3(z)*B());
}

EOD::EOD(Epoch epoch) : MOD(epoch) {
    double t = epoch.with_reference_epoch(J2000).get_days() / 36525;
    // Compute mean obliquity
    double eps_a = as2rad(
        84381.406 
        -46.836769*t
        -0.0001831*pow(t,2)
        +0.00200340*pow(t,3)
        +5.76e-7*pow(t,4)
        +4.34e-8*pow(t,5)
    );
    this->dcm = this->dcm * R1(eps_a);
}