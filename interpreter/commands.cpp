#include <iostream>

#include "commands.hpp"
#include "State.hpp"

// -------------------- WrongCommandArgsException --------------------

WrongCommandArgsException::WrongCommandArgsException(
    const std::string& command_name,
    const std::vector<std::string>& args
) {
    error_msg += "wrong arguments to command ";
    error_msg += command_name;
    error_msg += ": ";
    for (const auto& arg : args) {
        error_msg += arg + " ";
    }
}

const char* WrongCommandArgsException::what() const noexcept {
    return error_msg.c_str();
}

// -------------------- Commands --------------------

void BEGINCommand::exec(State& state) const {
    // TODO
}

void ENDCommand::exec(State& state) const {
    state.registers.pc_register = state.code.size();
}

void PUSHCommand::exec(State& state) const {
    state.stack.push(value);
}

void POPCommand::exec(State& state) const {
    state.stack.pop();
}

void PUSHRCommand::exec(State& state) const {
    state.stack.push(state.registers[reg]);
}

void POPRCommand::exec(State& state) const {
    state.registers[reg] = state.stack.pop();
}

void ADDCommand::exec(State& state) const {
    state.stack.push(state.stack.pop() + state.stack.pop());
}

void SUBCommand::exec(State& state) const {
    state.stack.push(state.stack.pop() - state.stack.pop());
}

void MULCommand::exec(State& state) const {
    state.stack.push(state.stack.pop() * state.stack.pop());
}

void DIVCommand::exec(State& state) const {
    state.stack.push(state.stack.pop() / state.stack.pop());
}

void OUTCommand::exec(State& state) const {
    std::cout << state.stack.top() << std::endl;
}

void INCommand::exec(State& state) const {
    int x;
    std::cin >> x;
    state.stack.push(x);
}

void JMPCommand::exec(State& state) const {
    state.registers.pc_register = state.labels.at(label);
}

void JEQCommand::exec(State& state) const {
    if (state.stack.pop() == state.stack.pop()) {
        state.registers.pc_register = state.labels.at(label);
    }
}

void JNECommand::exec(State& state) const {
    if (state.stack.pop() != state.stack.pop()) {
        state.registers.pc_register = state.labels.at(label);
    }
}

void JACommand::exec(State& state) const {
    if (state.stack.pop() > state.stack.pop()) {
        state.registers.pc_register = state.labels.at(label);
    }
}

void JAECommand::exec(State& state) const {
    if (state.stack.pop() >= state.stack.pop()) {
        state.registers.pc_register = state.labels.at(label);
    }
}

void JBCommand::exec(State& state) const {
    if (state.stack.pop() < state.stack.pop()) {
        state.registers.pc_register = state.labels.at(label);
    }
}

void JBECommand::exec(State& state) const {
    if (state.stack.pop() <= state.stack.pop()) {
        state.registers.pc_register = state.labels.at(label);
    }
}

void CALLCommand::exec(State& state) const {
    state.call_stack.push(state.registers.pc_register + 1);
    state.registers.pc_register = state.labels.at(label);
}

void RETCommand::exec(State& state) const {
    state.registers.pc_register = state.call_stack.pop();
}
