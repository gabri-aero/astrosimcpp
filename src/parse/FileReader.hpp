#ifndef _FILE_READER_HPP_
#define _FILE_READER_HPP_

#include <math/Matrix.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

class FileReader {

public:
    static math::matrix read(std::string filename, char delimiter = ',') {
        std::ifstream file(filename); 

        if (!file.is_open()) {
            std::cerr << "Error: file was not opened!" << std::endl;
        }

        std::string line;
        math::matrix data;
        math::vector data_row;

        while(getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            while(getline(ss, item, delimiter)) {
                data_row.push_back(std::stod(item));
            }
            data.push_back(data_row);
            data_row.clear();
        }

        return data;
    }

};

#endif // _FILE_READER_HPP_