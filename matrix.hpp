#ifndef INTERPRETER_MATRIX_H
#define INTERPRETER_MATRIX_H
#include <cstddef>
#include <vector>

namespace matrix_interpreter {

class Matrix {
public:
    Matrix() noexcept;
    Matrix(std::size_t rows, std::size_t columns);
    int &at(std::size_t i, std::size_t j);
    [[nodiscard]] int at(std::size_t i, std::size_t j) const noexcept;
    void print() const noexcept;
    void print(std::size_t rows, std::size_t columns) const;

    void add(const Matrix &rhs);
    void mul(const Matrix &rhs);

private:
    [[maybe_unused]] std::size_t rows_;
    [[maybe_unused]] std::size_t columns_;
    std::vector<std::vector<int>> data_;
};

}  // namespace matrix_interpreter
#endif  // INTERPRETER_MATRIX_H
