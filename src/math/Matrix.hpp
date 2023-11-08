#include <vector>
#include <array>
#include <stdexcept>
#include <math/Vector.hpp>
#include <iostream>

#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

namespace math {

class matrix : public std::vector<math::vector> {
public:
    using std::vector<math::vector>::vector;

    matrix(std::initializer_list<math::vector> ilist) : std::vector<math::vector>(ilist) {};

    bool operator==(const matrix& other);
    matrix operator+(const matrix& other);
    matrix operator-(const matrix& other);
    matrix operator*(const matrix& other);
    math::vector operator*(const math::vector& v);

    matrix dot(const matrix& other); // element-wise multiplication

    math::vector dim() const;

    static matrix zeros(int rows, int cols);
    static matrix zeros(math::vector);

    matrix T() const;
    matrix transpose() const;

    
    friend std::ostream& operator<<(std::ostream& os, const matrix& A) {
        for(auto row: A) {
            os << row << std::endl;
        }
        return os;
    }

    friend void check_dim(const matrix& A, const matrix& B) {
        if(A.dim().at(0) != B.dim().at(0)) {
            throw std::invalid_argument("Matrix sizes are not compatible");
        } else if(A.dim().at(1) != B.dim().at(1)) {
            throw std::invalid_argument("Matrix sizes are not compatible");
        }
    }

};

}

#endif //_MATRIX_HPP_