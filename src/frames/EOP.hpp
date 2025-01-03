#ifndef _EOP_HPP_
#define _EOP_HPP_

#include <time/TimeSeries.hpp>
#include <math/Vector.hpp>
#include <math/Utils.hpp>
#include <math/Matrix.hpp>
#include <math/Rotation.hpp>
#include <array>

class EOP : public math::vector {
public:
    double xp, yp, dUT1, lod, dX, dY;
    EOP() = default;
    EOP(double xp, double yp, double dUT1, double lod, double dX, double dY): math::vector{xp, yp, dUT1, lod, dX, dY},
        xp(this->at(0)),
        yp(this->at(1)),
        dUT1(this->at(2)),
        lod(this->at(3)),
        dX(this->at(4)),
        dY(this->at(5)) {
    };
    EOP(const double& value): EOP(value, value, value, value, value, value) {
    };  
    EOP(const math::vector& data): EOP(data.at(0), data.at(1), data.at(2), data.at(3), data.at(4), data.at(5)) {
    };
};

class EOPData : public TimeSeries<EOP> {
    bool loaded;
    std::string eop_file;
public:
    EOPData(std::string eop_file = "eopc04_14_IAU2000.62-now.txt"); 
    void load();
    EOP get(Epoch epoch);
};

extern EOPData eop_data;

#endif //_EOP_HPP_