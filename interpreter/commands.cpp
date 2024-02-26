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

void BEGINCommand::exec(State&) const {}

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
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    state.stack.push(lhs + rhs);
}

void SUBCommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    state.stack.push(lhs - rhs);
}

void MULCommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    state.stack.push(lhs * rhs);
}

void DIVCommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    state.stack.push(lhs / rhs);
}

void OUTCommand::exec(State& state) const {
    std::cout << state.stack.pop() << std::endl;
}

void INCommand::exec(State& state) const {
    int x;
    std::cin >> x;
    state.stack.push(x);
}

void DUPCommand::exec(State& state) const {
    auto v = state.stack.top();
    state.stack.push(v);
}

void JMPCommand::exec(State& state) const {
    state.registers.pc_register = state.labels[label];
}

void JEQCommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    if (lhs == rhs) {
        state.registers.pc_register = state.labels[label];
    }
}

void JNECommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    if (lhs != rhs) {
        state.registers.pc_register = state.labels[label];
    }
}

void JACommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    if (lhs > rhs) {
        state.registers.pc_register = state.labels[label];
    }
}

void JAECommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    if (lhs >= rhs) {
        state.registers.pc_register = state.labels[label];
    }
}

void JBCommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    if (lhs < rhs) {
        state.registers.pc_register = state.labels[label];
    }
}

void JBECommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    if (lhs <= rhs) {
        state.registers.pc_register = state.labels[label];
    }
}

void CALLCommand::exec(State& state) const {
    state.call_stack.push(state.registers.pc_register);
    state.registers.pc_register = state.labels[label];
}

void RETCommand::exec(State& state) const {
    state.registers.pc_register = state.call_stack.pop();
}
