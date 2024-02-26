#include "State.hpp"
#include "Labels.hpp"

State::State(const Code& code, const Labels& labels)
  : code(code),
    labels(labels)
{}

void State::run() {
    registers.pc_register = labels[LabelName::BEGIN_LABEL];
    while (registers.pc_register < code.size()) {
        ++registers.pc_register;
        code[registers.pc_register - 1]->exec(*this);
    }
}
