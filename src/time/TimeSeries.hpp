#ifndef _TIME_SERIES_HPP_
#define _TIME_SERIES_HPP_

#include <time/Epoch.hpp>
#include <math/Vector.hpp>
#include <math/Interpolation.hpp>
#include <memory>

template <typename Tp>
class TimeSeries : public math::Vector<std::pair<double, Tp>> {
protected:
    BaseInterpolator<double, Tp>* interpolator; 
    // TO DO: make interpolator point to *this to avoid having to call update_interpolator_data
    double epoch2days(Epoch epoch) const {
        return epoch.with_reference_epoch(J2000).with_timescale(TAI).get_days();
    }
    Epoch days2epoch(double days) const {
        return Epoch{days, TAI, J2000};
    }
public:
    TimeSeries() {
        // Default interpolator = LinearInterpolators
        this->interpolator = new LinearInterpolator<double,Tp>();
    };
    TimeSeries(const math::Vector<Epoch>& x, const math::Vector<Tp>& y) {
        int N = x.size();
        for(int i=0; i<N; i++) {
            this->add(x.at(i), y.at(i));
        }
        TimeSeries();
        this->update_interpolator_data();
    }
    void add(const Epoch& epoch, const Tp& y) {
        this->push_back({epoch2days(epoch), y});
    }
    void add(const double& t, const Tp& y) {
        this->push_back({t, y});
    }
    Tp get(Epoch epoch) const {
        double t = epoch2days(epoch);
        return interpolator->interpolate(t);
    }
    void set_interpolator(BaseInterpolator<double, Tp>& interpolator) {
        this->interpolator = &interpolator;
        this->update_interpolator_data();
    }
    void update_interpolator_data() {
        this->interpolator->set_data(*this);
    }
    // Time dt in days
    TimeSeries<Tp> fixed_time_series(double dt) {
        double start = this->at(0).first;
        double size = this->size();
        double end = this->at(size-1).first;
        double t = start;
        TimeSeries<Tp> fixed_time_series;
        Epoch epoch;
        while(t<end) {
            fixed_time_series.add(t, this->interpolator->interpolate(t));
            t += dt;
        }
        return fixed_time_series;
    }
};


#endif //_TIME_SERIES_HPP_