#include "State.hpp"
#include "commands.hpp" // TODO: delete me
#include "parse.hpp"

int main() {
    auto [code, labels] = parse_code_file("PUSH 1 PUSH 2 ADD OUT");
    State state(code, labels);
    state.run();
    for (auto* command : code) {
        delete command;
    }
}
