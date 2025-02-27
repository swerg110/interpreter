#include "interpreter.h"
#include <algorithm>
#include <fstream>
#include "interpreter_exceptions.h"
#include "iostream"
#include "sstream"
#include "string"

namespace matrix_interpreter {

void Interpreter::parse_command(const std::string &raw_command) {
    tokens.clear();
    raw_command_ = raw_command;
    std::istringstream iss(raw_command);
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }
}

void Interpreter::run_command() {
    if (tokens.empty()) {
        //        return;
        throw invalid_command_format();
    }

    const auto command = get_command();
    switch (command) {
        case LOAD:
            load();
            break;
        case PRINT:
            print();
            break;
        case EXIT:
            exit();
            break;
        case ELEM:
            elem();
            break;
        case ADD:
            add();
            break;
        case MUL:
            mul();
            break;
        case BAD_COMMAND:
            throw unknown_command(tokens[0]);
    }
}

void Interpreter::load() {
    if (is_good_tokens_size(Commands::LOAD)) {
        const std::size_t reg_num = parse_register(tokens[1]);
        const std::string filename = tokens[2];
        std::ifstream file(filename);
        if (!file) {
            throw unable_to_open_file(filename);
        }

        std::size_t row_count;     // NOLINT(cppcoreguidelines-init-variables)
        std::size_t column_count;  // NOLINT(cppcoreguidelines-init-variables)
        if (!(file >> row_count >> column_count)) {
            throw invalid_file_format();
        }
        if (row_count == 0 || column_count == 0) {
            regs[reg_num] = Matrix();
            return;
        }

        Matrix matrix(row_count, column_count);
        for (std::size_t i = 0; i < row_count; i++) {
            for (std::size_t j = 0; j < column_count; j++) {
                int el;  // NOLINT(cppcoreguidelines-init-variables)
                if (!(file >> el)) {
                    throw invalid_file_format();
                }
                matrix.at(i, j) = el;
            }
        }
        regs[reg_num] = std::move(matrix);

    } else {
        throw invalid_command_format();
    }
}

void Interpreter::print() {
    if (is_good_tokens_size(Commands::PRINT)) {
        const std::size_t reg = parse_register(tokens[1]);
        matrix_from_register(reg).print();
    } else {
        throw invalid_command_format();
    }
}

void Interpreter::exit() {
    if (is_good_tokens_size(Commands::EXIT)) {
        std::exit(0);  // NOLINT(concurrency-mt-unsafe,
    }
    throw invalid_command_format();
}

void Interpreter::elem() {
    if (is_good_tokens_size(Commands::ELEM)) {
        const std::size_t reg = parse_register(tokens[1]);
        const std::size_t row = parse_matrix_dimension(tokens[2]);
        const std::size_t column = parse_matrix_dimension(tokens[3]);
        matrix_from_register(reg).print(row, column);
    } else {
        throw invalid_command_format();
    }
}

void Interpreter::add() {
    if (is_good_tokens_size(Commands::ADD)) {
        const std::size_t reg_a = parse_register(tokens[1]);
        const std::size_t reg_b = parse_register(tokens[2]);

        matrix_from_register(reg_a).add(matrix_from_register(reg_b));

    } else {
        throw invalid_command_format();
    }
}

void Interpreter::mul() {
    if (is_good_tokens_size(Commands::MUL)) {
        const std::size_t reg_a = parse_register(tokens[1]);
        const std::size_t reg_b = parse_register(tokens[2]);

        matrix_from_register(reg_a).mul(matrix_from_register(reg_b));
    } else {
        throw invalid_command_format();
    }
}

void Interpreter::run() {
    std::string command;
    while (std::getline(std::cin, command)) {
        try {
            parse_command(command);
            run_command();
        } catch (std::bad_alloc &) {
            std::cout << "Unable to allocate memory"
                      << "\n";

        } catch (std::exception &e) {
            std::cout << e.what() << '\n';
        }
    }
}

Commands Interpreter::get_command() {
    const std::string cmd = tokens[0];
    auto it = command_map.find(cmd);
    if (it != command_map.end()) {
        return it->second;
    }

    return BAD_COMMAND;
}

std::size_t Interpreter::parse_register(const std::string &token) {
    if (!is_valid_register(token)) {
        throw not_register(token);
    }
    return static_cast<std::size_t>(token[1] - '0');
}

Matrix &Interpreter::matrix_from_register(std::size_t reg) {
    return regs[reg];
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
std::size_t Interpreter::parse_matrix_dimension(const std::string &token
) const {
    std::istringstream stream(token);
    std::size_t value;  // NOLINT(cppcoreguidelines-init-variables)
    char remaining;     // NOLINT(cppcoreguidelines-init-variables)

    if (!(stream >> value) || stream.get(remaining) ||
        value > MAX_MATRIX_SIZE) {
        throw invalid_command_format();
    }
    return value;
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
inline bool Interpreter::is_valid_register(const std::string &reg) {
    return reg.size() == 2 && reg[0] == '$' &&
           std::isdigit(reg[1]  // NOLINT(readability-implicit-bool-conversion)
           ) &&
           // cppcheck-suppress unsignedPositive
           static_cast<std::size_t>(reg[1] - '0') >= MIN_REGISTER_NUM &&
           static_cast<std::size_t>(reg[1] - '0') <= MAX_REGISTER_NUM;
}

inline bool Interpreter::is_good_tokens_size(const Commands &cmd) {
    switch (cmd) {
        case LOAD:
            return tokens.size() == 3;
        case PRINT:
            return tokens.size() == 2;
        case EXIT:
            return tokens.size() == 1;
        case ELEM:
            return tokens.size() == 4;
        case ADD:  // NOLINT(bugprone-branch-clone)
            return tokens.size() == 3;
        case MUL:
            return tokens.size() == 3;
        case BAD_COMMAND:  // NOLINT(bugprone-branch-clone)
            return false;
        default:
            return false;
    }
}
}  // namespace matrix_interpreter
