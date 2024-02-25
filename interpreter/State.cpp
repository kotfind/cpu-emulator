#include "State.hpp"

State::State(const Code& code, const Labels& labels)
  : code(code),
    labels(labels)
{}

void State::run() {
    while (registers.pc_register < code.size()) {
        ++registers.pc_register;
        code[registers.pc_register - 1]->exec(*this);
    }
}
