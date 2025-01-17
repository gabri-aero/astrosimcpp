#ifndef _IAU_2000_HPP_
#define _IAU_2000_HPP_

// TO DO: improve precision of X, Y, s

#include <frames/EOP.hpp>
#include <frames/BaseFrame.hpp>

class BaseITRF : public BaseFrame {
    // tab5.2a
    std::array<double, 1600> Aa, Ba; // A = a_{s,j}_i, Api; B = a_{c,j}_i
    std::array<std::array<double, 14>, 1600> a; // Coefficients for l, lp, F, D, Om, L_Me, L_Ve, L_E, L_Ma, L_J, L_Sa, L_U, L_Ne, pa
    // tab5.2b
    std::array<double, 1275> Ab, Bb;
    std::array<std::array<double, 14>, 1275> b; // Coefficients for l, lp, F, D, Om, L_Me, L_Ve, L_E, L_Ma, L_J, L_Sa, L_U, L_Ne, pa
    // tab5.2d
    std::array<double, 66> Ad, Bd;
    std::array<std::array<double, 14>, 66> d; // Coefficients for l, lp, F, D, Om, L_Me, L_Ve, L_E, L_Ma, L_J, L_Sa, L_U, L_Ne, pa
public:
    BaseITRF();
    std::array<long double,3> get_XYs(const Epoch& epoch) const;
    math::matrix PN(const Epoch& epoch) const;
    math::matrix R(const Epoch& epoch) const;
    math::matrix W(const Epoch& epoch) const;
    math::matrix get_dcm(const Epoch& epoch) const override;
};

/**
 * Frame bias matrix that allows conversion from EME2000 to GCRF
 */
math::matrix B();

class BaseCIRF : public BaseITRF {
public:
    using BaseITRF::BaseITRF;
    math::matrix get_dcm(const Epoch& epoch) const override final;
};

class BaseTIRF : public BaseITRF {
public:
    using BaseITRF::BaseITRF;
    math::matrix get_dcm(const Epoch& epoch) const override final;
};

class BasePEF : public BaseITRF {
public:
    using BaseITRF::BaseITRF;
    math::matrix get_dcm(const Epoch& epoch) const override final;
};

// Define Earth intermediate frames
extern const BaseITRF ITRF; // Internation Terrestrial Reference Frame
extern const BaseCIRF CIRF; // Celestial Intermediate Reference Frame
extern const BaseTIRF TIRF; // Terrestrial Intermediate Reference Frame
extern const BasePEF PEF; // Pseudo Earth Fixed Frame


#endif // _IAU_2000_HPP_