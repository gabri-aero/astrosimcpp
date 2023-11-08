#include "Matrix.hpp"


math::vector math::matrix::dim() const {
    double rows = this->size(); // implementation of math::vector needs this to be a integer
    double cols = this->at(0).size();
    return math::vector{rows, cols};
}

math::matrix math::matrix::zeros(int rows, int cols) {
    math::vector row;
    math::matrix A;
    for(int j=0; j<cols; j++) {
        row.push_back(0);
    }
    for(int i=0; i<rows; i++) {
        A.push_back(row);
    }
    return A;
}

math::matrix math::matrix::zeros(math::vector dim) {
    int rows = static_cast<int>(dim.at(0));
    int cols = static_cast<int>(dim.at(1));
    return zeros(rows, cols);
}

math::matrix math::matrix::transpose() const {
    int rows = this->dim().at(0);
    int cols = this->dim().at(1);

    auto T = math::matrix::zeros(cols, rows);

    for(int i=0; i < rows; i++) {
        for(int j=0; j < cols; j++) {
            T[j][i] = (*this)[i][j];
        }
    }
    return T;
}

math::matrix math::matrix::T() const {
    return this->transpose();
}

bool math::matrix::operator==(const math::matrix& B) {
    math::matrix A = *this;
    try {
        check_dim(A, B);
        int rows = A.dim().at(0);
        for(int i = 0; i < rows; i++) {
            if(A.at(i) != B.at(i)) {
                return false;
            }
        }
    } catch (const std::invalid_argument& e) {
        return false;
    }
    return true;
}

math::matrix math::matrix::operator+(const math::matrix& B) {
    math::matrix A = *this;
    check_dim(A, B);

    // allocate result matrix
    math::matrix C = zeros(A.dim());

    // iterate over elements
    for(int i=0; i < A.dim()[0]; i++) {
        for(int j=0; j < A.dim()[1]; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
};

math::matrix math::matrix::operator-(const math::matrix& B) {
    math::matrix A = *this;
    check_dim(A, B);

    // allocate result matrix
    math::matrix C = zeros(A.dim());

    // iterate over elements
    for(int i=0; i < A.dim()[0]; i++) {
        for(int j=0; j < A.dim()[1]; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;
};


math::matrix math::matrix::operator*(const matrix& B) {
    math::matrix A = *this;
    if(A.dim().at(1) != B.dim().at(0)) {
        throw std::invalid_argument("Matrix are not compatible for multiplication");
    }
    int k = A.dim().at(1); // common dimension

    int rows = A.dim().at(0);
    int cols = B.dim().at(1);

    math::matrix C = zeros(rows, cols);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            for(int m = 0; m < k; m++) {
                C[i][j] += A[i][m] * B[m][j];
            }
        }
    }

    return C;
}

math::vector math::matrix::operator*(const math::vector& v) {
    int rows = this->dim().at(0);
    int cols = this->dim().at(1);

    auto result = math::vector::zeros(rows);

    if (cols != v.size()) {
        throw std::invalid_argument("Matrix and column vector do not have compatible size for multiplication");
    }
    for(int i=0; i < rows; i++) {
        for(int j=0; j < cols; j++) {
            result[i] += (*this)[i][j] * v[j];
        }
    }
    return result;
}

math::matrix math::matrix::dot(const math::matrix& B) {
    math::matrix A = *this;
    check_dim(A, B);

    // allocate result matrix
    math::matrix C = zeros(A.dim());

    // iterate over elements
    for(int i=0; i < A.dim()[0]; i++) {
        for(int j=0; j < A.dim()[1]; j++) {
            C[i][j] = A[i][j] * B[i][j];
        }
    }

    return C;
};