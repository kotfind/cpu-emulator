#include "commands.hpp"

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

const char* WrongCommandArgsException::what() {
    return error_msg.c_str();
}

void BEGINCommand::exec(State& state) const {
    throw "TODO";
}

void ENDCommand::exec(State& state) const {
    throw "TODO";
}

void PUSHCommand::exec(State& state) const {
    throw "TODO";
}

void POPCommand::exec(State& state) const {
    throw "TODO";
}

void PUSHRCommand::exec(State& state) const {
    throw "TODO";
}

void POPRCommand::exec(State& state) const {
    throw "TODO";
}

void ADDCommand::exec(State& state) const {
    throw "TODO";
}

void SUBCommand::exec(State& state) const {
    throw "TODO";
}

void MULCommand::exec(State& state) const {
    throw "TODO";
}

void DIVCommand::exec(State& state) const {
    throw "TODO";
}

void OUTCommand::exec(State& state) const {
    throw "TODO";
}

void INCommand::exec(State& state) const {
    throw "TODO";
}

void JMPCommand::exec(State& state) const {
    throw "TODO";
}

void JEQCommand::exec(State& state) const {
    throw "TODO";
}

void JNECommand::exec(State& state) const {
    throw "TODO";
}

void JACommand::exec(State& state) const {
    throw "TODO";
}

void JAECommand::exec(State& state) const {
    throw "TODO";
}

void JBCommand::exec(State& state) const {
    throw "TODO";
}

void JBECommand::exec(State& state) const {
    throw "TODO";
}

void CALLCommand::exec(State& state) const {
    throw "TODO";
}

void RETCommand::exec(State& state) const {
    throw "TODO";
}
