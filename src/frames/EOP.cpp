#include "EOP.hpp"
#include <fstream>

EOPData::EOPData(std::string eop_file) 
: eop_file{eop_file}, loaded{false} {
    
}

EOP EOPData::get(Epoch epoch) {
    if(!loaded) load();
    return TimeSeries<EOP>::get(epoch);
}

void EOPData::load() {
    std::cout << "Loading EOP data" << std::endl;
    std::string iers_dir{IERS_DIR};
    std::ifstream eop_path(iers_dir + '/' + eop_file);
    
    std::string line;
    int year, month, day, mjd;
    double x, y, dut1, lod, dx, dy;
    
    // Read the file line by line using a while loop
    while (std::getline(eop_path, line)) {
        if((line[0] != '#') && (line[0]!=' ') && (line[0]!='\0')) {
            std::istringstream iss(line);
            iss >> year >> month >> day >> mjd >> x >> y >> dut1 >> lod >> dx >> dy;
            EOP eop{x, y, dut1, lod, dx, dy};
            Epoch epoch{year, month, day, 0, 0, 0, UTC};
            this->add(epoch, eop);
        }
    }
    this->interpolator = new CubicSplineInterpolator<double,EOP>();
    this->update_interpolator_data();
    
    loaded = true;
};


// Declare global eop_data variable
EOPData eop_data;