#ifndef _EPHEMERIS_BODY_HPP_
#define _EPHEMERIS_BODY_HPP_

#include <bodies/NaturalBody.hpp>

class EphemerisBody : public NaturalBody {
private:
    std::string ref_body;
    std::string frame;
public:
    EphemerisBody(std::string name, std::string ref_body, std::string frame);
    void set_sv(Epoch epoch);
};

#endif // _EPHEMERIS_BODY_HPP_