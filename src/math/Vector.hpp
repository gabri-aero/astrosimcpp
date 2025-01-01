#include <math.h>
#include <vector>
#include <iostream>
#include <initializer_list>
#include <stdexcept> 
#include <algorithm>

#ifndef _MATH_HPP_
#define _MATH_HPP_


namespace math {

template<typename A, typename B>
using V = typename std::common_type<A,B>::type;

/**
 * @class Vector
 * 
 * @brief It handles common vector operations
*/
template<typename T>
class Vector : public std::vector<T> {
public:
    using std::vector<T>::vector; // get std::vector<T> constructors
    
    /**
     * @brief Vector constructor from initializer list
     * @param ilist vector components. Ex: {1, 2, 3, 4}.
    */
    Vector(std::initializer_list<T> ilist) : std::vector<T>(ilist) {}
    Vector(const math::Vector<T>& vector) : std::vector<T>(vector) {}
    Vector(const std::vector<T>& vector) : std::vector<double>(vector) {}

    template<typename U>
    explicit operator Vector<U>() const {
        Vector<U> result(this->size());
        std::transform(
            this->begin(), 
            this->end(),
            result.begin(),
            [](T item) { return static_cast<U>(item); }
        );
        return result;
    }

    /**
     * @brief Create empty vector with zeros
     * @param N vector length
    */
    static Vector zeros(int N) {
        math::Vector<T> vec;
        T zero;
        zero = 0;
        for(int i=0; i<N; i++) {
            vec.push_back(zero);
        }
        return vec;
    }

    // Operator overloading
    Vector<T>& operator=(const T& value) {
        for (auto& element : *this) {
            element = value;
        }
        return *this;
    }

    template<typename U>
    bool operator==(const Vector<U>& v2) {
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

    template<typename U>
    Vector<V<T,U>> operator+(const Vector<U>& v2) const {
        
        if(this->size() != v2.size()) {
            throw std::runtime_error("Vectors to be added have different dimensions");
        }
        Vector<V<T,U>> sum;
        for(int i=0; i<this->size(); i++) {
            sum.push_back(this->at(i) + v2.at(i));
        }
        return sum;
    }
    
    template<typename U>
    Vector<V<T,U>> operator-(const Vector<U>& v2) const {
        if(this->size() != v2.size()) {
            throw std::runtime_error("Vectors to be added have different dimensions");
        }
        Vector<V<T,U>> sum;
        for(int i=0; i<this->size(); i++) {
            sum.push_back(this->at(i) - v2.at(i));
        }
        return sum;
    }
    
    template<typename U>
    void operator+=(const Vector<U>& v2) {
        if(this->size() != v2.size()) {
            throw std::runtime_error("Vectors to be added have different dimensions");
        }
        *this = *this + v2;
    }

    Vector<T> operator/(double scalar) const {
        math::Vector<T> result;
        for(int i=0; i<this->size(); i++) {
            result.push_back(this->at(i)/scalar);
        }
        return result;
    }

    /**
     * @brief Scalar product
    */
    template<typename U>
    friend Vector<U> operator*(double scalar, const Vector<U>& v);

    /**
     * @brief Scalar product
    */
    template<typename U>
    friend Vector<U> operator*(const Vector<U>& v, double scalar);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& v);

    // Overload std::vector methods
    void push_back(T value) {
        std::vector<T>::push_back(value); // Call the base class method
    }
    
    void push_back(Vector<T> vec) {
        for(auto value: vec) {
            std::vector<T>::push_back(value);
        } // Call the base class method
    }

    /**
     * @brief Get only a part of the vector
    */
    math::Vector<T> subvec(int start, int end) const {
        math::Vector<T> v;
        for(int i=start; i<end; i++) {
            v.push_back(this->at(i));
        }
        return v;
    }
};

/**
 * @brief Scalar product
*/
template<typename U>
Vector<U> operator*(double scalar, const Vector<U>& v) {
    math::Vector<U> result;
    for(int i=0; i<v.size(); i++) {
        result.push_back(v.at(i)*scalar);
    }
    return result;
}

/**
 * @brief Scalar product
*/
template<typename U>
Vector<U> operator*(const Vector<U>& v, double scalar) {
    return scalar*v;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Vector<U>& v) {
    os << "[ ";
    for(auto i: v) {
        os << i << " ";
    }
    os << "]";
    return os;
}

inline namespace defaults {
    using vector = Vector<double>;
}

};

/**
 * @brief Euclidean/L2 norm
*/
template<typename T>
math::V<double, T> norm(math::Vector<T> vec) {
    math::V<double, T> sum=0;
    for(auto i: vec) {
        sum += i*i;
    }
    return sqrt(sum);
}

/**
 * @brief Vector dot product
*/
template<typename T, typename U>
math::V<U,T> dot(math::Vector<T> v1, math::Vector<U> v2) {
    double sum=0;
    for(int i=0; i<v1.size(); i++) {
        sum += v1[i]*v2[i];
    }
    return sum;
}

/**
 * @brief Vector cross product
*/
template<typename T, typename U>
math::Vector<math::V<U,T>> cross(math::Vector<T> v1, math::Vector<U> v2) {
    return {
        v1[1] * v2[2] - v2[1] * v1[2],
        -v1[0] * v2[2] + v2[0] * v1[2],
        v1[0] * v2[1] - v2[0] * v1[1]
    };
}

#endif //_MATH_HPP_