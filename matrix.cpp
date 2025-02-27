#include "matrix.hpp"
#include "iostream"
#include "matrix_exceptions.h"

namespace matrix_interpreter {
Matrix::Matrix() noexcept : rows_(0), columns_(0), data_(0) {
}

Matrix::Matrix(std::size_t rows, std::size_t columns)
    : rows_(rows), columns_(columns), data_(rows, std::vector<int>(columns)) {
}

int &Matrix::at(std::size_t i, std::size_t j) {
    return data_[i][j];
}

int Matrix::at(std::size_t i, std::size_t j) const noexcept {
    return data_[i][j];
}

void Matrix::print() const noexcept {
    for (std::size_t i = 0; i < rows_; i++) {
        for (std::size_t j = 0; j < columns_; j++) {
            std::cout << at(i, j) << (j + 1 == columns_ ? "" : " ");
        }
        std::cout << "\n";
    }
}

void Matrix::print(std::size_t rows, std::size_t columns) const {
    if (rows >= rows_ || columns >= columns_) {
        throw element_is_out_of_bounds();
    }

    std::cout << data_[rows][columns] << '\n';
}

void Matrix::add(const Matrix &rhs) {
    if (rows_ != rhs.rows_) {
        throw dimension_mismatch(rows_, rhs.rows_);
    }
    if (columns_ != rhs.columns_) {
        throw dimension_mismatch(columns_, rhs.columns_);
    }

    for (std::size_t i = 0; i < data_.size(); i++) {
        for (std::size_t j = 0; j < data_[i].size(); j++) {
            data_[i][j] += rhs.data_[i][j];
        }
    }
}

void Matrix::mul(const Matrix &rhs) {
    if (columns_ != rhs.rows_) {
        throw dimension_mismatch(columns_, rhs.rows_);
    }

    Matrix buffer_matrix(rows_, rhs.columns_);
    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < rhs.columns_; ++j) {
            int64_t sum = 0;
            for (std::size_t k = 0; k < columns_; ++k) {
                sum += static_cast<int64_t>(data_[i][k]) * rhs.data_[k][j];
            }

            buffer_matrix.at(i, j) = static_cast<int>(sum);
        }
    }

    *this = std::move(buffer_matrix);
}
}  // namespace matrix_interpreter
