/*
Assignment 5
Student ID: 10138372
*/
#include <iostream>
#include <stdexcept>
#include <string>
template <typename T>
class Matrix {
private:
    size_t rows_;
    size_t cols_;
    T* data_;
public:
    // Default constructor
    Matrix() : rows_{ 0 }, cols_{ 0 }, data_{ nullptr } {
        std::cout << "";
    }
    // Constructor that creates a matrix of specified dimensions
    Matrix(size_t rows, size_t cols) : rows_{ rows }, cols_{ cols } {
        std::cout << "";
        try {
            data_ = new T[rows * cols];
        }
        catch (const std::bad_alloc& e) {
            throw std::runtime_error("Memory allocation failed for matrix of size " + std::to_string(rows) + "x" + std::to_string(cols));
        }
        for (size_t i{}; i < rows_; ++i) {
            for (size_t j{}; j < cols_; ++j) {
                data_[i * cols_ + j] = 0;
            }
        }
    }
    // Copy constructor
    Matrix(const Matrix& other) : rows_{ other.rows_ }, cols_{ other.cols_ }, data_{ new T[rows_ * cols_] } {
        std::cout << "";
        for (size_t i{}; i < rows_; ++i) {
            for (size_t j{}; j < cols_; ++j) {
                data_[i * cols_ + j] = other.data_[i * cols_ + j];
            }
        }
    }
    // Destructor
    ~Matrix() {
        std::cout << "";
        delete[] data_;
    }
    // Assignment operator
    Matrix& operator=(const Matrix& other) {
        std::cout << "";
        if (&other == this) {
            return *this;
        }
        delete[] data_;
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = new T[rows_ * cols_];
        for (size_t i{}; i < rows_; ++i) {
            for (size_t j{}; j < cols_; ++j) {
                data_[i * cols_ + j] = other.data_[i * cols_ + j];
            }
        }
        return *this;
    }
    size_t rows() const {
        return rows_;
    }
    size_t cols() const {
        return cols_;
    }
    // Overloaded operator() functions to access the elements of the matrix using row and column indice
    T operator()(size_t row, size_t col) const { return data_[row * cols_ + col]; }
    T& operator()(size_t row, size_t col) { return data_[row * cols_ + col]; }
    Matrix(Matrix&& other) noexcept : rows_{ other.rows_ }, cols_{ other.cols_ }, data_{ other.data_ } {
        std::cout << "";
        other.data_ = nullptr;
        other.rows_ = 0;
        other.cols_ = 0;
    }
    // Move assignment operator
    Matrix& operator=(Matrix&& other) noexcept {
        std::cout << "";
        if (&other == this) {
            return *this;
        }
        delete[] data_;
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = other.data_;
        other.data_ = nullptr;
        other.rows_ = 0;
        other.cols_ = 0;
        return *this;
    }
    // Overload output operator
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (size_t i = 0; i < matrix.rows_; ++i) {
            for (size_t j = 0; j < matrix.cols_; ++j) {
                os << matrix(i, j) << " ";
            }
            os << std::endl;
        }
        return os;
    }
    // Add matrices
    Matrix operator+(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition");
        }
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result(i, j) = data_[i * cols_ + j] + other(i, j);
            }
        }
        return result;
    }
    // Subtract matrices
    Matrix operator-(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
        }
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result(i, j) = data_[i * cols_ + j] - other(i, j);
            }
        }
        return result;
    }
    // Multiply matrices
    Matrix operator*(const Matrix& other) const {
        if (cols_ != other.rows_) {
            throw std::invalid_argument("Number of columns in the first matrix must be equal to the number of rows in the second matrix");
        }
        Matrix result(rows_, other.cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < other.cols_; ++j) {
                double sum = 0;
                for (size_t k = 0; k < cols_; ++k) {
                    sum += data_[i * cols_ + k] * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }
    // Remove ith row and jth column from the matrix
    Matrix removeRowAndCol(size_t i, size_t j) const {
        if (i >= rows_ || j >= cols_) {
            throw std::out_of_range("Index out of range");
        }
        Matrix result(rows_ - 1, cols_ - 1);
        size_t row_offset = 0;
        for (size_t row = 0; row < rows_; ++row) {
            if (row == i) {
                row_offset = 1;
                continue;
            }
            size_t col_offset = 0;
            for (size_t col = 0; col < cols_; ++col) {
                if (col == j) {
                    col_offset = 1;
                    continue;
                }
                result(row - row_offset, col - col_offset) = data_[row * cols_ + col];
            }
        }
        return result;
    }
    // Calculates determinant for square matrices
    double determinant() const {
        if (rows_ != cols_) {
            throw std::invalid_argument("Matrix must be square to compute determinant");
        }

        if (rows_ == 1) {
            return data_[0];
        }
        else if (rows_ == 2) {
            return data_[0] * data_[3] - data_[1] * data_[2];
        }
        else {
            double det = 0;
            for (size_t j = 0; j < cols_; ++j) {
                Matrix minor_matrix = removeRowAndCol(0, j);
                det += (j % 2 == 0 ? 1 : -1) * data_[j] * minor_matrix.determinant();
            }
            return det;
        }
    }
};

template <typename T>
// Overload insertion to output stream for matrices
std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
    for (size_t i = 0; i < mat.rows(); ++i) {
        for (size_t j = 0; j < mat.cols(); ++j) {
            os << mat(i, j);
            if (j < mat.cols() - 1) {
                os << ' ';
            }
        }
        if (i < mat.rows() - 1) {
            os << '\n';
        }
    }
    return os;
}

int main() {
    // Create a 3x3 matrix with default values
    Matrix<double> A;
    Matrix<double> B;
    Matrix<double> C;
    try {
        A = Matrix<double>(3, 3);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    try {
        B = Matrix<double>(3, 3);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    try {
        C = Matrix<double>(2, 3);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    // Set the matrix elements for matrices
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;
    A(1, 0) = 9;
    A(1, 1) = 8;
    A(1, 2) = 7;
    A(2, 0) = 4;
    A(2, 1) = 2;
    A(2, 2) = 6;

    B(0, 0) = 5;
    B(0, 1) = 5;
    B(0, 2) = 4;
    B(1, 0) = 1;
    B(1, 1) = 2;
    B(1, 2) = 3;
    B(2, 0) = 6;
    B(2, 1) = 9;
    B(2, 2) = 8;

    C(0, 0) = 3;
    C(0, 1) = 4;
    C(0, 2) = 1;
    C(1, 0) = 2;
    C(1, 1) = 5;
    C(1, 2) = 6;
    // Prints the matrices
    std::cout << "Matrix A: " << std::endl;
    for (size_t i{}; i < A.rows(); ++i) {
        for (size_t j{}; j < A.cols(); ++j) {
            std::cout << A(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Matrix B: " << std::endl;
    for (size_t i{}; i < B.rows(); ++i) {
        for (size_t j{}; j < B.cols(); ++j) {
            std::cout << B(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Matrix C: " << std::endl;
    for (size_t i{}; i < C.rows(); ++i) {
        for (size_t j{}; j < C.cols(); ++j) {
            std::cout << C(i, j) << " ";
        }
        std::cout << std::endl;
    }
    // Copy the matrix
    Matrix<double> m2 = A;
    // Change a value in the original matrix
    m2(0, 1) = 4;
    std::cout << "m2 (copy of A with element (0, 1) changed to 4):" << std::endl;
    std::cout << m2;
    // Prints matrices
    std::cout << "Original matrix A:" << std::endl;
    for (size_t i{}; i < A.rows(); ++i) {
        for (size_t j{}; j < A.cols(); ++j) {
            std::cout << A(i, j) << " ";
        }
        std::cout << std::endl;
    }
    Matrix<double> m3 = std::move(A);
    std::cout << "m3 (after move of A):" << std::endl;
    std::cout << m3;
    try {
        Matrix<double> sum = m3 + B;
        std::cout << "A + B:" << std::endl;
        std::cout << sum << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    try {
        Matrix<double> difference = m3 - B;

        std::cout << "A - B:" << std::endl;
        std::cout << difference << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    try {
        Matrix<double> product = m3 * B;
        std::cout << "A * B:" << std::endl;
        std::cout << product << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    try {
        Matrix<double> product = B * C;
        std::cout << "A * C:" << std::endl;
        std::cout << product << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    try {
        Matrix<double> removed = m3.removeRowAndCol(0, 0);;
        std::cout << "Matrix A with row 1 and column 1 removed: " << std::endl;
        std::cout << removed << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    double det = B.determinant();
    std::cout << "Determinant of B: " << det << std::endl;
    return 0;
}
