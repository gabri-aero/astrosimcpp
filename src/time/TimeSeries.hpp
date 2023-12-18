#include <time/Epoch.hpp>
#include <vector>

#ifndef _TIME_SERIES_HPP_
#define _TIME_SERIES_HPP_

template <typename T>
class TimeSeries : public std::vector<std::pair<Epoch, T>> {
public:
    /**
     * @brief Function that pushes back Epoch, T pair element
    */
    void add(const Epoch& epoch, const T& value) {
        this->push_back(std::make_pair(epoch, value));
    }
    /**
     * @brief Retrieves T object given an input Epoch. It applies interpolation.
     * @param epoch
    */
    T get(Epoch epoch) { // TO DO: check that Epoch lies within TimeSeries range
        int i = 0;
        while(this->at(i).first <= epoch) {
            i++;
        }
        i--; // move one step back
        if(this->at(i).first == epoch) {
            return this->at(i).second;
        } else {
            double step = this->at(i+1).first - this->at(i).first;
            double dt = epoch - this->at(i).first;
            T dvalue = this->at(i+1).second - this->at(i).second;
            T obj = this->at(i).second + dvalue * dt/step;
            return obj;
        }
    }
    /**
     * @brief This function converts not equally spaced TimeSeries vector to a evenly distributed TimeSeries by means of interpolation
     * @param dt time step
    */
    TimeSeries<T> interpolate(double dt) {
        Epoch epoch = this->at(0).first; // set epoch to start
        Epoch end = this->back().first; // get end epoch
        TimeSeries<T> time_series; // fixed step time series
        while(epoch <= end) {
            time_series.add(epoch, get(epoch));
            epoch = epoch.add_secs(dt);
        }
        return time_series;
    }
};


#endif //_TIME_SERIES_HPP_