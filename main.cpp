#include "matrix.hpp"
#ifdef _MSC_VER
#include <crtdbg.h>
#endif
#include "interpreter.h"
#include "iostream"

int main() {
#ifdef _MSC_VER
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif
    try {
        matrix_interpreter::Interpreter interpreter;
        interpreter.run();
    } catch (const std::exception &e) {
        std::cout << e.what() << "\n";
        return 1;
    }
    return 0;
}
