#include <vector>
#include <array>
#include <stdexcept>
#include <math/Vector.hpp>
#include <iostream>
#include <algorithm>

#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

namespace math {

// Some forward declarations
template<typename Tp>
class LowerTriangular;

template<typename Tp>
class UpperTriangular;

template<typename A, typename B>
using V = typename std::common_type<A,B>::type;
/**
 * @class Matrix
 * 
 * @brief It handles the main matrix operations
*/
template<typename Tp>
class Matrix : public math::Vector<math::Vector<Tp>> {
public:
    using math::Vector<math::Vector<Tp>>::Vector; // get std::vector constructors
    /**
     * @brief Constructor that enables a double initializer list
     * 
     * @param ilist - double initializer list. Ex: {{1, 2, 3}, {3, 4, 5}}
    */
    Matrix(std::initializer_list<math::Vector<Tp>> ilist) : math::Vector<math::Vector<Tp>>(ilist) {};

    template<typename Up>
    explicit operator Matrix<Up>() const {
        Matrix<Up> result(this->size());
        std::transform(
            this->begin(), 
            this->end(),
            result.begin(),
            [](math::Vector<Tp> row) { return static_cast<math::Vector<Up>>(row); }
        );
        return result;
    }

    // Operator overloading
    Matrix<Tp>& operator=(const Tp& value) {
        for (auto& element : *this) {
            element = value;
        }
        return *this;
    }

    bool operator==(const Matrix<Tp>& other) {
        try {
            check_dim(*this, other); // check they have same size
            int rows = this->dim().first;
            for(int i = 0; i < rows; i++) { // loop over all matrix elements
                if(this->at(i) != other.at(i)) {
                    return false;
                }
            }
        } catch (const std::invalid_argument& e) {
            // catch exception because of not same size
            return false;
        }
        return true;
    }

    template<typename Up>
    Matrix<V<Tp,Up>> operator+(const Matrix<Up>& other) {
        check_dim(*this, other);

        // allocate result matrix
        Matrix<V<Tp,Up>> result = zeros(this->dim());

        // iterate over elements
        for(int i=0; i < this->dim().first; i++) {
            for(int j=0; j < this->dim().second; j++) {
                result[i][j] = (*this)[i][j] + other[i][j];
            }
        }

        return result;
    };

    template<typename Up>
    Matrix<V<Tp,Up>> operator-(const Matrix<Up>& other) {
        check_dim(*this, other);

        // allocate result matrix
        Matrix<V<Tp,Up>> result = zeros(this->dim());

        // iterate over elements
        for(int i=0; i < this->dim().first; i++) {
            for(int j=0; j < this->dim().second; j++) {
                result[i][j] = (*this)[i][j] - other[i][j];
            }
        }

        return result;
    };
    /**
     * @brief Matrix product
    */
    template<typename Up>
    Matrix<V<Tp,Up>> operator*(const Matrix<Up>& other) {
        // Check compatibility for matrix multiplication
        if(this->dim().second != other.dim().first) {
            throw std::invalid_argument("Matrix are not compatible for multiplication");
        }
        int k = this->dim().second; // common dimension

        // Resulting matrix dimension
        int rows = this->dim().first;
        int cols = other.dim().second;

        // Pre-allocate result
        Matrix<V<Tp,Up>> result = zeros(rows, cols);

        // Perform matrix product
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                for(int m = 0; m < k; m++) {
                    result[i][j] += (*this)[i][m] * other[m][j];
                }
            }
        }

        return result;
    }
    /**
     * @brief Vector product
    */
    template<typename Up>
    math::Vector<V<Tp,Up>> operator*(const math::Vector<Up>& v) {
        int rows = this->dim().first;
        int cols = this->dim().second;

        auto result = math::Vector<V<Tp,Up>>::zeros(rows); // Pre-allocate result

        // Check compatibility for multiplication
        if (cols != v.size()) {
            throw std::invalid_argument("Matrix and column vector do not have compatible size for multiplication");
        }

        // Perform multiplication
        for(int i=0; i < rows; i++) {
            for(int j=0; j < cols; j++) {
                result[i] += (*this)[i][j] * v[j];
            }
        }
        return result;
    }

    /**
     * @brief Matrix element-wise multiplication
    */
    template<typename Up>
    Matrix<V<Tp,Up>> dot(const Matrix<Up>& other) {
        check_dim(*this, other); // check compatibility for element-wise multiplication

        // allocate result matrix
        math::Matrix<V<Tp,Up>> result = zeros(this->dim());

        // iterate over elements
        for(int i=0; i < this->dim().first; i++) {
            for(int j=0; j < this->dim().second; j++) {
                result[i][j] = (*this)[i][j] * other[i][j];
            }
        }

        return result;
    };

    /**
     * @brief Retrieve matrix dimension
    */
    std::pair<int,int> dim() const {
        int rows = this->size(); 
        int cols = this->at(0).size();
        return {rows, cols};
    }

    /**
     * @brief Create matrix object with zeros and input dimensions
     * @param rows
     * @param cols
    */
    static Matrix<Tp> zeros(int rows, int cols) {
        math::Vector<Tp> row;
        math::Matrix<Tp> A;
        // Create empty row
        for(int j=0; j<cols; j++) {
            row.push_back(0);
        }
        // Append rows nrows times
        for(int i=0; i<rows; i++) {
            A.push_back(row);
        }
        return A;
    }

    /**
     * @brief Create matrix object with zeros and input dimensions. 
     * Note that math::vector shall have size 2
     * @param rows - rows
     * @param cols - columns
    */
    static Matrix<Tp> zeros(std::pair<int,int> dim) {
        auto [rows, cols] = dim;
        // Delegate function
        return zeros(rows, cols);
    }
    
    /**
     * @brief Create identity matrix object of size NxN
     * @param N
    */
    static Matrix<Tp> eye(int N) {
        Matrix<Tp> A = zeros(N, N);
        for(int i=0; i<N; i++) {
            A[i][i] = 1;
        }
        return A;
    }

    /**
     * @brief New matrix object is created as the transposed matrix.
    */
    Matrix<Tp> T() const {
        // Alternative call. Then, delegate.
        return this->transpose();
    }
    /**
     * @brief New matrix object is created as the transposed matrix.
    */
    Matrix<Tp> transpose() const {
        // Retrieve matrix dimension
        auto [rows, cols] = this->dim();

        // Pre-allocate transpose accordingly
        Matrix<Tp> t = zeros(cols, rows);

        // Assign transpose elements (i,j) -> (j,i)
        for(int i=0; i < rows; i++) {
            for(int j=0; j < cols; j++) {
                t[j][i] = (*this)[i][j];
            }
        }
        return t;
    }

    template<typename Up>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<Up>& A);

    /**
     * @brief Check that two matrices dimension is equal
    */
    template<typename A_, typename B_>
    friend void check_dim(const Matrix<A_>& A, const Matrix<B_>& B); 

    // Factorization algorithms
    std::pair<math::LowerTriangular<V<Tp,double>>, math::UpperTriangular<V<Tp,double>>> crout() const {
        int n = this->dim().first; // TO DO: check that it is square
        auto L = math::LowerTriangular<V<Tp,double>>::eye(n);
        auto U = math::UpperTriangular<V<Tp,double>>::eye(n);
        auto A = *this;

        // Crout factorization algorithm
        L.at(0,0) = A[0][0];
        U.at(0,1) = A[0][1]/L.at(0,0);
        for(int i=1; i<n-1; i++) {
            L.at(i,i-1) = A[i][i-1];
            L.at(i,i) = A[i][i]-L.at(i,i-1)*U.at(i-1,i);
            U.at(i,i+1) = A[i][i+1]/L.at(i,i);
        }
        L.at(n-1,n-2) = A[n-1][n-2];
        L.at(n-1,n-1) = A[n-1][n-1]-L.at(n-1,n-2)*U.at(n-2,n-1);
        return std::make_pair(L,U);
    }

    // Methods for solving linear systems
    template<typename Up>
    math::Vector<Up> crout(const math::Vector<Up>& b) const {
        // Compute Crout factorization
        auto [L, U] = this->crout();
        int n = L.dim();
        // Initialize z and x
        auto z = math::Vector<Up>::zeros(n);
        auto x = math::Vector<Up>::zeros(n);

        // Solve system Lz=b
        z[0] = b[0]/L.at(0,0);
        for(int i=1; i<n; i++) {
            z[i] = (b[i]-L.at(i,i-1)*z[i-1]) / L.at(i,i);
        }
        // Solve system Ux=z
        x[n-1] = z[n-1];
        for(int i=n-2; i>=0; i--) {
            x[i]=z[i]-x[i+1]*U.at(i,i+1);
        }
        return x;
    }
};

template<typename Up>
std::ostream& operator<<(std::ostream& os, const Matrix<Up>& A){
    for(auto row: A) {
        os << row << '\n';
    }
    return os;
}

template<typename A_, typename B_>
void check_dim(const Matrix<A_>& A, const Matrix<B_>& B){
    if(A.dim().first != B.dim().first) {
        throw std::invalid_argument("Matrix sizes are not compatible");
    } else if(A.dim().second != B.dim().second) {
        throw std::invalid_argument("Matrix sizes are not compatible");
    }
}


inline namespace defaults {
    using matrix = Matrix<double>;
}

template<typename Tp>
class LowerTriangular {
protected:
    Tp* data;
    int size_ = 0;
    int dim_ = 0;
    Tp off_diagonal_value = 0;
    int triangular(int value) const {
        return value*(value+1)/2;
    }
public:
     // Constructor to initialize from an initializer list
    LowerTriangular(std::initializer_list<Tp> init) {
        int N = init.size();
        dim_ = N < 1 ? N : 1;
        while(N > 1) {
            dim_++;
            N -= dim_;
        }
        size_ = init.size();
        // Allocate memory
        data = new Tp[size_];
        int i = 0;
        for (const auto& value : init) {
            data[i++] = value;
        }
    }
    LowerTriangular(int N) {
        dim_ = N;
        size_ = triangular(N);
        // Allocate memory
        data = new Tp[size_];
    }
    // Copy constructor for deep copy
    LowerTriangular(const LowerTriangular<Tp>& other) {
        dim_ = other.dim();
        size_ = other.size();
        // Allocate memory
        data = new Tp[size_];
        // Copy other data into data
        std::copy(other.data, other.data+size_, data);
    }
    static LowerTriangular zeros(int N) {
        LowerTriangular<Tp> A(N);
        for(int i=0; i<A.size(); i++) {
            A.data[i] = 0;
        }
        return A;
    }

    static LowerTriangular eye(int N) {
        LowerTriangular<Tp> A(N);
        for(int i=0; i<A.size(); i++) {
            A.data[i] = 0;
        }
        for(int i=0; i<A.dim(); i++) {
            A.at(i, i) = 1;
        }
        return A;
    }
    Tp& at(int row, int col) {
        return col > row ? off_diagonal_value : data[triangular(row)+col];
    }
    const Tp& at(int row, int col) const {
        return col > row ? off_diagonal_value : data[triangular(row)+col];
    }

    template<typename Up>
    math::Vector<V<Tp,Up>> operator*(const math::Vector<Up> v) {
        if(this->dim() != v.size()) std::cout << "Incompatible sizes";
        math::Vector<V<Tp,Up>> result = math::Vector<V<Tp,Up>>::zeros(this->dim());
        for(int i=0; i<this->dim(); i++) {
            for(int j=0; j<=i; j++) {
                result[i] += this->at(i,j)*v[j];
            }
        }
        return result;
    }

    int dim() const {
        return dim_;
    }
    int size() const {
        return size_;
    }
    
    template<typename Up>
    friend std::ostream& operator<<(std::ostream& os, const LowerTriangular<Up>& L);

    // Destructor to free allocated data
    ~LowerTriangular() {
        delete[] data;
    }
};

template<typename Up>
std::ostream& operator<<(std::ostream& os, const LowerTriangular<Up>& L){
    for(int row=0; row<L.dim(); row++) {
        os << "[ ";
        for(int col=0; col<L.dim(); col++) {
            os << L.at(row, col) << " ";
        }
        os << "]" << '\n';
    }
    return os;
}

template<typename Tp>
class UpperTriangular : public LowerTriangular<Tp> {
public:
    using LowerTriangular<Tp>::LowerTriangular;
    
    static UpperTriangular zeros(int N) {
        UpperTriangular<Tp> A(N);
        for(int i=0; i<A.size(); i++) {
            A.data[i] = 0;
        }
        return A;
    }

    static UpperTriangular eye(int N) {
        UpperTriangular<Tp> A(N);
        for(int i=0; i<A.size(); i++) {
            A.data[i] = 0;
        }
        for(int i=0; i<A.dim(); i++) {
            A.at(i, i) = 1;
        }
        return A;
    }
    Tp& at(int row, int col) {
        return col < row ? this->off_diagonal_value : this->data[row*this->dim()-this->triangular(row)+col];
    }
    const Tp& at(int row, int col) const {
        return col < row ? this->off_diagonal_value : this->data[row*this->dim()-this->triangular(row)+col];
    }
    template<typename Up>
    math::Vector<V<Tp,Up>> operator*(const math::Vector<Up> v) {
        if(this->dim() != v.size()) std::cout << "Incompatible sizes";
        math::Vector<V<Tp,Up>> result = math::Vector<V<Tp,Up>>::zeros(this->dim());
        for(int i=0; i<this->dim(); i++) {
            for(int j=i; j<=this->dim(); j++) {
                result[i] += this->at(i,j)*v[j];
            }
        }
        return result;
    }
};

template<typename Up>
std::ostream& operator<<(std::ostream& os, const UpperTriangular<Up>& U){
    for(int row=0; row<U.dim(); row++) {
        os << "[ ";
        for(int col=0; col<U.dim(); col++) {
            os << U.at(row, col) << " ";
        }
        os << "]" << '\n';
    }
    return os;
}

template<typename Tp>
class BandMatrix {
    Tp* data;
    int above=0; // Number of off-diagonals above main diagonal
    int below=0; // Number of off-diagonals below mian diagonal
    int size=0; // Data size
    int N=0; // Matrix dimensions
    Tp off_diagonal_value=0;
    int triangular(int value) const {
        return value*(value+1)/2;
    }
public:
    BandMatrix(int dim, int above, int below) : N(dim), above(above), below(below) {
        // Allocate data
        size = N*N-triangular(N-below-1)-triangular(N-above-1);
        data = new Tp[size];
    };
    BandMatrix(std::initializer_list<Tp> ilist, int dim, int above, int below) : BandMatrix(dim, above, below) {
        int i = 0;
        if(ilist.size() != this->size) throw std::out_of_range("Initializer list size does not match band matrix non-zero elements");
        for (const Tp& value : ilist) {
            data[i++] = value;
        }
    }
    // Static
    static BandMatrix zeros(int N, int above, int below) {
        BandMatrix<Tp> A(N, above, below);
        for(int i=0; i<A.size; i++) {
            A.data[i] = 0;
        }
        return A;
    }

    static BandMatrix eye(int N, int above, int below) {
        BandMatrix<Tp> A(N, above, below);
        for(int i=0; i<A.size; i++) {
            A.data[i] = 0;
        }
        for(int i=0; i<A.dim(); i++) {
            A.at(i, i) = 1;
        }
        return A;
    }
    // Copy constructor for deep copy
    BandMatrix(const BandMatrix<Tp>& other) {
        N = other.N;
        size = other.size;
        above = other.above;
        below = other.below;
        // Allocate memory
        data = new Tp[size];
        // Copy other data into data
        std::copy(other.data, other.data+size, data);
    }

    int dim() const {
        return N;
    }
    Tp& at(int row, int col) {
        if(col > row+above || col < row-below) return off_diagonal_value;
        // Compute global idx
        int zeros_above = row >= N-above-1 ? triangular(N-above-1) : triangular(N-above-1) - triangular(N-row-1-above);
        int zeros_below = row < below ? 0 : triangular(row-below);
        int idx = N*row - zeros_above - zeros_below + col;
        return data[idx];
    }
    const Tp& at(int row, int col) const {
        if(col > row+above || col < row-below) return off_diagonal_value;
        // Compute global idx
        int zeros_above = row >= N-above-1 ? triangular(N-above-1) : triangular(N-above-1) - triangular(N-row-1-above);
        int zeros_below = row < below ? 0 : triangular(row-below);
        int idx = N*row - zeros_above - zeros_below + col;
        return data[idx];
    }
    // Factorization algorithms
    std::pair<BandMatrix<V<Tp,double>>, BandMatrix<V<Tp,double>>> crout() const {
        int n = this->dim(); // TO DO: check that it is square
        BandMatrix<V<Tp,double>> L(n, 0, this->below);
        BandMatrix<V<Tp,double>> U(n, this->above, 0);
        auto A = *this;

        // Crout factorization algorithm
        L.at(0,0) = A.at(0,0);
        U.at(0,1) = A.at(0,1)/L.at(0,0);
        U.at(0,0) = 1;
        for(int i=1; i<n-1; i++) {
            L.at(i,i-1) = A.at(i,i-1);
            L.at(i,i) = A.at(i,i)-L.at(i,i-1)*U.at(i-1,i);
            U.at(i,i+1) = A.at(i,i+1)/L.at(i,i);
            U.at(i,i) = 1;
        }
        L.at(n-1,n-2) = A.at(n-1,n-2);
        L.at(n-1,n-1) = A.at(n-1,n-1)-L.at(n-1,n-2)*U.at(n-2,n-1);
        U.at(n-1,n-1) = 1;
        return std::make_pair(L,U);
    }
    template<typename Up>
    math::Vector<Up> crout(const math::Vector<Up>& b) const {
        // Compute Crout factorization
        auto [L, U] = this->crout();
        int n = L.dim();
        // Initialize z and x
        auto z = math::Vector<Up>::zeros(n);
        auto x = math::Vector<Up>::zeros(n);

        // Solve system Lz=b
        z[0] = b[0]/L.at(0,0);
        for(int i=1; i<n; i++) {
            z[i] = (b[i]-L.at(i,i-1)*z[i-1]) / L.at(i,i);
        }
        // Solve system Ux=z
        x[n-1] = z[n-1];
        for(int i=n-2; i>=0; i--) {
            x[i]=z[i]-x[i+1]*U.at(i,i+1);
        }
        return x;
    }
    
    template<typename Up>
    friend std::ostream& operator<<(std::ostream& os, const BandMatrix<Up>& L);

    ~BandMatrix() {
        delete[] data;
    }
};

template<typename Up>
std::ostream& operator<<(std::ostream& os, const BandMatrix<Up>& matrix){
    for(int row=0; row<matrix.dim(); row++) {
        os << "[ ";
        for(int col=0; col<matrix.dim(); col++) {
            os << matrix.at(row, col) << " ";
        }
        os << "]" << '\n';
    }
    return os;
}

}

#endif //_MATRIX_HPP_