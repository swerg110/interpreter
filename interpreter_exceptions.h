//
// Created by Sergei on 2/6/25.
//

#ifndef INTERPRETER_INTERPRETER_EXCEPTIONS_H
#define INTERPRETER_INTERPRETER_EXCEPTIONS_H
#include "string"

namespace matrix_interpreter {

struct unknown_command : std::runtime_error {
    explicit unknown_command(const std::string &cmd)
        : std::runtime_error("Unknown command: '" + cmd + "'") {
    }
};

struct invalid_command_format : std::runtime_error {
    explicit invalid_command_format()
        : std::runtime_error("Invalid command format") {
    }
};

struct unable_to_open_file : std::runtime_error {
    explicit unable_to_open_file(const std::string &filename)
        : std::runtime_error("Unable to open file '" + filename + "'") {
    }
};

struct invalid_file_format : std::runtime_error {
    explicit invalid_file_format() : std::runtime_error("Invalid file format") {
    }
};

struct not_register : std::runtime_error {
    explicit not_register(const std::string &reg)
        : std::runtime_error("'" + reg + "' is not a register") {
    }
};

}  // namespace matrix_interpreter
#endif  // INTERPRETER_INTERPRETER_EXCEPTIONS_H
