#include <math.h>
#include <vector>
#include <iostream>
#include <initializer_list>
#include <stdexcept> 

#ifndef _MATH_HPP_
#define _MATH_HPP_

namespace math {
/**
 * @class vector
 * 
 * @brief It handles common vector operations
*/
class vector : public std::vector<double> {
public:
    using std::vector<double>::vector; // get std::vector<double> constructors
    
    /**
     * @brief Vector constructor from initializer list
     * @param ilist vector components. Ex: {1, 2, 3, 4}.
    */
    vector(std::initializer_list<double> ilist) : std::vector<double>(ilist) {}

    /**
     * @brief Create empty vector with zeros
     * @param N vector length
    */
    static vector zeros(int N) {
        math::vector vec;
        for(int i=0; i<N; i++) {
            vec.push_back(0);
        }
        return vec;
    }

    // Operator overloading

    bool operator==(const vector& v2) {
        if(this->size() != v2.size()) {
            return false;
        } else {
            for(int i = 0; i < this->size(); i++) {
                if(this->at(i) != v2.at(i)) {
                    return false;
                }
            }
        }
        return true;
    }

    vector operator+(const vector& v2) const {
        if(this->size() != v2.size()) {
            throw std::runtime_error("Vectors to be added have different dimensions");
        }
        vector sum;
        for(int i=0; i<this->size(); i++) {
            sum.push_back(this->at(i) + v2.at(i));
        }
        return sum;
    }
    
    vector operator-(const vector& v2) const {
        if(this->size() != v2.size()) {
            throw std::runtime_error("Vectors to be added have different dimensions");
        }
        vector sum;
        for(int i=0; i<this->size(); i++) {
            sum.push_back(this->at(i) - v2.at(i));
        }
        return sum;
    }
    
    void operator+=(const vector& v2) {
        if(this->size() != v2.size()) {
            throw std::runtime_error("Vectors to be added have different dimensions");
        }
        *this = *this + v2;
    }

    vector operator/(double scalar) {
        math::vector result;
        for(int i=0; i<this->size(); i++) {
            result.push_back(this->at(i)/scalar);
        }
        return result;
    }

    /**
     * @brief Scalar product
    */
    friend vector operator*(double scalar, const vector& v) {
        math::vector result;
        for(int i=0; i<v.size(); i++) {
            result.push_back(v.at(i)*scalar);
        }
        return result;
    }

    /**
     * @brief Scalar product
    */
    friend vector operator*(const vector& v, double scalar) {
        return scalar*v;
    }

    friend std::ostream& operator<<(std::ostream& os, const vector& v) {
        os << "[ ";
        for(auto i: v) {
            os << i << " ";
        }
        os << "]";
        return os;
    }

    // Overload std::vector methods

    void push_back(double value) {
        std::vector<double>::push_back(value); // Call the base class method
    }
    
    void push_back(vector vec) {
        for(auto value: vec) {
            std::vector<double>::push_back(value);
        } // Call the base class method
    }

    /**
     * @brief Get only a part of the vector
    */
    math::vector subvec(int start, int end) const {
        math::vector v;
        for(int i=start; i<end; i++) {
            v.push_back(this->at(i));
        }
        return v;
    }
};

};

/**
 * @brief Euclidean/L2 norm
*/
double norm(math::vector vec);

/**
 * @brief Vector dot product
*/
double dot(math::vector v1, math::vector v2);

/**
 * @brief Vector cross product
*/
math::vector cross(math::vector v1, math::vector v2);

#endif //_MATH_HPP_