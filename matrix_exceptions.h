#ifndef INTERPRETER_MATRIX_EXCEPTIONS_H
#define INTERPRETER_MATRIX_EXCEPTIONS_H
#include "string"

namespace matrix_interpreter {

struct element_is_out_of_bounds : std::runtime_error {
    explicit element_is_out_of_bounds()
        : std::runtime_error("Requested element is out of bounds") {
    }
};

struct dimension_mismatch : std::runtime_error {
    explicit dimension_mismatch(const size_t col, const size_t row)
        : std::runtime_error(
              "Dimension mismatch: lhs=" + std::to_string(col) +
              ", rhs=" + std::to_string(row)
          ) {
    }
};
}  // namespace matrix_interpreter
#endif  // INTERPRETER_MATRIX_EXCEPTIONS_H
