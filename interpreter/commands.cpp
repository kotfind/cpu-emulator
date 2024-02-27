#include <iostream>
#include <limits>

#include "commands.hpp"
#include "State.hpp"
#include "Exception.hpp"

// -------------------- Standard Commands --------------------
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
    int value;
    if (std::cin >> value) {
        state.stack.push(value);
    } else {
        throw WrongInputException();
    }
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

// -------------------- User-defined Commands --------------------

void DUPCommand::exec(State& state) const {
    auto v = state.stack.top();
    state.stack.push(v);
}

void ECHOCommand::exec(State&) const {
    std::cout << text << std::endl;
}
