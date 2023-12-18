#include <time/Epoch.hpp>
#include <vector>

#ifndef _TIME_SERIES_HPP_
#define _TIME_SERIES_HPP_

template <typename T>
class TimeSeries : public std::vector<std::pair<Epoch, T>> {
public:
    void add(const Epoch& epoch, const T& value) {
        this->push_back(std::make_pair(epoch, value));
    }
};


#endif //_TIME_SERIES_HPP_