#include <vector>
#include <array>
#include <stdexcept>
#include <math/Vector.hpp>
#include <iostream>

#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

namespace math {
/**
 * @class Matrix
 * 
 * @brief It handles the main matrix operations
*/
class matrix : public std::vector<math::vector> {
public:
    using std::vector<math::vector>::vector; // get std::vector constructors
    /**
     * @brief Constructor that enables a double initializer list
     * 
     * @param ilist - double initializer list. Ex: {{1, 2, 3}, {3, 4, 5}}
    */
    matrix(std::initializer_list<math::vector> ilist) : std::vector<math::vector>(ilist) {};

    // Operator overloading
    bool operator==(const matrix& other);
    matrix operator+(const matrix& other);
    matrix operator-(const matrix& other);
    /**
     * @brief Matrix product
    */
    matrix operator*(const matrix& other);
    /**
     * @brief Vector product
    */
    math::vector operator*(const math::vector& v);

    /**
     * @brief Matrix element-wise multiplication
    */
    matrix dot(const matrix& other); 

    /**
     * @brief Retrieve matrix dimension
    */
    math::vector dim() const;

    /**
     * @brief Create matrix object with zeros and input dimensions
     * @param rows
     * @param cols
    */
    static matrix zeros(int rows, int cols);

    /**
     * @brief Create matrix object with zeros and input dimensions. 
     * Note that math::vector shall have size 2
     * @param rows - rows
     * @param cols - columns
    */
    static matrix zeros(math::vector);

    /**
     * @brief New matrix object is created as the transposed matrix.
    */
    matrix T() const;
    /**
     * @brief New matrix object is created as the transposed matrix.
    */
    matrix transpose() const;

    
    friend std::ostream& operator<<(std::ostream& os, const matrix& A) {
        for(auto row: A) {
            os << row << std::endl;
        }
        return os;
    }

    /**
     * @brief Check that two matrices dimension is equal
    */
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