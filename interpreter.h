#ifndef INTERPRETER_INTERPRETER_H
#define INTERPRETER_INTERPRETER_H
#include "array"
#include "matrix.hpp"
#include "string"
#include "unordered_map"
#include "vector"

namespace matrix_interpreter {
constexpr std::size_t NUM_REGISTERS = 10;
constexpr std::size_t MIN_REGISTER_NUM = 0;
constexpr std::size_t MAX_REGISTER_NUM = 9;
constexpr std::size_t MAX_MATRIX_SIZE = 1000000;

enum Commands { LOAD, PRINT, EXIT, ELEM, ADD, MUL, BAD_COMMAND };

static const std::unordered_map<std::string, Commands> command_map = {
    {"load", LOAD}, {"print", PRINT}, {"exit", EXIT},
    {"elem", ELEM}, {"add", ADD},     {"mul", MUL}};

class Interpreter {
public:
    Interpreter() = default;
    void parse_command(const std::string &raw_command);
    void run();
    void run_command();

private:
    std::array<Matrix, NUM_REGISTERS> regs{};
    std::vector<std::string> tokens;
    std::string raw_command_;

    Commands get_command();

    void load();
    void print();
    void exit();
    void elem();

    void add();
    void mul();

    std::size_t parse_register(const std::string &token);
    Matrix &matrix_from_register(std::size_t reg);
    [[nodiscard]] std::size_t parse_matrix_dimension(const std::string &token
    ) const;
    inline bool is_valid_register(const std::string &reg);
    inline bool is_good_tokens_size(const Commands &cmd);
};
}  // namespace matrix_interpreter
#endif  // INTERPRETER_INTERPRETER_H
