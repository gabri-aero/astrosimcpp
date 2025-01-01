#ifndef _INTERPOLATION_HPP_
#define _INTERPOLATION_HPP_

#include<math/Matrix.hpp>

template <typename U, typename V>
class BaseInterpolator {
protected:
    math::Vector<std::pair<U,V>> data;
public:
    BaseInterpolator() = default;
    BaseInterpolator(const math::Vector<U>& x, const math::Vector<V>& y) {
        this->set_data(x, y);
    }
    BaseInterpolator(const math::Vector<std::pair<U,V>>& data) {
        this->set_data(data);
    }
    BaseInterpolator& operator=(const BaseInterpolator&) = default;
    /**
     * @brief Function where the interpolation method is defined.
     * @param x
    */
    virtual V interpolate(const U& x) const = 0;
    /**
     * @brief Independent variable values getter
    */
    math::Vector<U> get_x_values() const {
        math::Vector<U> x;
        for(const std::pair<U, V>& pair: data) {
            x.push_back(pair.first);
        }
        return x;
    }
    /**
     * @brief Getter for dependent variables data
    */
    math::Vector<V> get_y_values() const {
        math::Vector<V> y;
        for(const std::pair<U, V>& pair: data) {
            y.push_back(pair.second);
        }
        return y;
    }
    
    /**
     * @brief Function that pushes back U, V pair element
    */
    void add(const U& x, const V& y) {
        data.push_back({x, y});
    }
    /**
     * @brief Data setters
     */
    void set_data(const math::Vector<U>& x, const math::Vector<V>& y) {
        data.clear();
        int N = x.size();
        for(int i=0; i<N; i++) {
            this->add(x.at(i), y.at(i));
        }
    }
    virtual void set_data(const math::Vector<std::pair<U,V>>& data) {
        this->data = data;
    }
};


template <typename U, typename V>
class LinearInterpolator : public BaseInterpolator<U, V> {
public:
    using BaseInterpolator<U,V>::BaseInterpolator;

    V interpolate(const U& x) const final {
        int i = 0;
        double N = this->data.size();
        if(x >= this->data.at(N-1).first) { // If out-of-bounds retrieve y[end] or y[0]
            return this->data.at(N-1).second;
        } else if(x <= this->data.at(0).first) {
            return this->data.at(0).second;
        }
        while(this->data.at(i).first <= x) {
            i++;
        }
        i--; // move one step back
        if(this->data.at(i).first == x) {
            return this->data.at(i).second;
        } else {
            U step = this->data.at(i+1).first - this->data.at(i).first;
            U dx = x - this->data.at(i).first;
            V dy = this->data.at(i+1).second - this->data.at(i).second;
            V obj = this->data.at(i).second + dy * dx/step;
            return obj;
        }
    }
};

// Deduction guide to enable class template argument deduction
template <typename U, typename V>
LinearInterpolator(const math::Vector<U>&, const math::Vector<V>&) -> LinearInterpolator<U, V>;

template <typename U, typename V>
class CubicSplineInterpolator : public BaseInterpolator<U, V> {
    math::Vector<V> a, b, c, d; // Splines coefficients
public:
    using BaseInterpolator<U,V>::BaseInterpolator;
    
    CubicSplineInterpolator(const math::Vector<U>& x, const math::Vector<V>& y) : BaseInterpolator<U,V>(x,y) {
        this->compute_spline_coefficients();
    }

    void compute_spline_coefficients() {
        // Retrieve tabular data
        math::vector x = static_cast<math::vector>(this->get_x_values());
        math::Vector<V> y = this->get_y_values();
        // Data size
        int N = this->data.size();
        // Compute independent variable steps
        math::vector h;
        for(int j=0; j<N-1; j++) {
            h.push_back(x.at(j+1)-x.at(j));
        }
        // Set constant spline terms at nodes
        a = y;
        // Setup linear system
        math::Vector<V> alpha; // column vector
        V zeros = y.at(0);
        zeros = 0;
        alpha.push_back(zeros); // alpha_0=0
        for(int j=1; j<N-1; j++) {
            alpha.push_back(
                3/h.at(j)*(a.at(j+1)-a.at(j))-3/h.at(j-1)*(a.at(j)-a.at(j-1))
            );
        } 
        alpha.push_back(zeros); // aplha_end=0

        math::matrix A = math::matrix::eye(N);
        for(int i=1; i<N-1; i++) {
            auto& row = A.at(i);
            row.at(i-1) = h.at(i-1);
            row.at(i+1) = h.at(i);
            row.at(i) = 2*(h.at(i-1)+h.at(i));
        }
        // Solve tridiagonal system using Crout factorization
        c = A.crout(alpha);
        // Assign b and d coefficients
        b = math::Vector<V>::zeros(N-1);
        d = math::Vector<V>::zeros(N-1);
        for(int j=0; j<N-1; j++){
            b.at(j) = (a.at(j+1)-a.at(j))/h.at(j) - h.at(j)/3*(c.at(j+1)+2*c.at(j));
            d.at(j) = (c.at(j+1)-c.at(j))/(3*h.at(j));
        }
    }
    math::Vector<V> get_a() const {
        return a;
    }
    math::Vector<V> get_b() const {
        return b;
    }
    math::Vector<V> get_c() const {
        return c;
    }
    math::Vector<V> get_d() const {
        return d;
    }
    math::Vector<V> get_spline(int i) const {
        return math::Vector{a.at(i), b.at(i), c.at(i), d.at(i)};
    }

    V interpolate(const double& x) const final {
        int i = 0;
        int N = this->data.size();
        if(x >= this->data.at(N-1).first) { // If out-of-bounds retrieve y[end] or y[0]
            return this->data.at(N-1).second;
        } else if(x <= this->data.at(0).first) {
            return this->data.at(0).second;
        }
        while(this->data.at(i).first <= x) {
            i++;
        }
        i--; // move one step back
        // Get spline coefficients
        math::Vector<V> m = get_spline(i);
        double dx = x - this->data.at(i).first;
        return m[0] + m[1]*dx + m[2]*dx*dx + m[3]*dx*dx*dx;
    }
    void set_data(const math::Vector<std::pair<U,V>>& data) override {
        BaseInterpolator<U,V>::set_data(data);
        this->compute_spline_coefficients();
    }
};

// Deduction guide to enable class template argument deduction
template <typename U, typename V>
CubicSplineInterpolator(const math::Vector<U>&, const math::Vector<V>&) -> CubicSplineInterpolator<U, V>;


#endif //_INTERPOLATION_HPP_