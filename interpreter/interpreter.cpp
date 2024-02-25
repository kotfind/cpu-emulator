#include "State.hpp"
#include "parse.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

void usage(const char* exec_name) {
    std::cerr
        << "Usage:\n"
        << exec_name << " file"
        << std::endl;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        usage(argv[0]);
        return -1;
    }

    std::ifstream file(argv[1]);
    std::string code_string;
    if (file.is_open()) {
        std::ostringstream ss;
        ss << file.rdbuf();
        code_string = ss.str();
        file.close();
    } else {
        std::cerr << "cannot open file: " << argv[1] << std::endl;
        return -1;
    }

    auto [code, labels] = parse_code_file(code_string);

    State state(code, labels);
    state.run();

    for (auto* command : code) {
        delete command;
    }
}
