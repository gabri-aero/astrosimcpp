#ifndef _EPHEMERIS_BODY_HPP_
#define _EPHEMERIS_BODY_HPP_

#include <bodies/NaturalBody.hpp>

class EphemerisBody : public NaturalBody {
private:
    std::string ref_body;
    std::string frame;
public:
    EphemerisBody(std::string name, std::string ref_body = "UNDEFINED", std::string frame = "UNDEFINED");
    void set_sv(Epoch epoch);
    void set_orientation(Epoch epoch);
    void set_ref_body(std::string ref_body);
    void set_frame(std::string frame);
};

#endif // _EPHEMERIS_BODY_HPP_