#include "Command.hpp"
#include "State.hpp"
#include "Exception.hpp"

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <limits>

// -------------------- Defines --------------------

#define NO_ARG_COMMAND(name) \
    class name##Command : public Command { \
        public: \
            name##Command() {} \
            ~name##Command() {} \
                                \
            void exec(State&) const override; \
                                                    \
            static Command* create(const std::vector<std::string>& args) { \
                if (args.size() != 0) { \
                    throw WrongCommandArgsException(#name, args); \
                } \
                  \
                return new name##Command(); \
            } \
    };

#define INT_ARG_COMMAND(name) \
    class name##Command : public Command { \
        public: \
            name##Command(int value) : value(value) {} \
            ~name##Command() {} \
                                \
            void exec(State&) const override; \
                                                    \
            static Command* create(const std::vector<std::string>& args) { \
                if (args.size() != 1) { \
                    throw WrongCommandArgsException(#name, args); \
                } \
                  \
                int value; \
                try { \
                    value = std::stoi(args[0]); \
                } catch (const std::invalid_argument&) { \
                    throw WrongCommandArgsException(#name, args); \
                } \
                  \
                return new name##Command(value); \
            } \
              \
        private: \
            int value; \
    };

#define REG_ARG_COMMAND(name) \
    class name##Command : public Command { \
        public: \
            name##Command(const RegisterName& reg) : reg(reg) {} \
            ~name##Command() {} \
                                \
            void exec(State&) const override; \
                                                    \
            static Command* create(const std::vector<std::string>& args) { \
                if (args.size() != 1) { \
                    throw WrongCommandArgsException(#name, args); \
                } \
                  \
                return new name##Command(RegisterName(args[0])); \
            } \
              \
        private: \
            RegisterName reg; \
    };

#define LABEL_ARG_COMMAND(name) \
    class name##Command : public Command { \
        public: \
            name##Command(const LabelName& label) : label(label) {} \
            ~name##Command() {} \
                                \
            void exec(State&) const override; \
                                                    \
            static Command* create(const std::vector<std::string>& args) { \
                if (args.size() != 1) { \
                    throw WrongCommandArgsException(#name, args); \
                } \
                  \
                return new name##Command(LabelName(args[0])); \
            } \
              \
        private: \
            LabelName label; \
    };

#define COMMAND_CREATE_FUNCTION(name) name##Command::create

// -------------------- Standard Commands --------------------
NO_ARG_COMMAND(END)
void ENDCommand::exec(State& state) const {
    state.registers.pc_register = state.code.size();
}

INT_ARG_COMMAND(PUSH)
void PUSHCommand::exec(State& state) const {
    state.stack.push(value);
}

NO_ARG_COMMAND(POP)
void POPCommand::exec(State& state) const {
    state.stack.pop();
}

REG_ARG_COMMAND(PUSHR)
void PUSHRCommand::exec(State& state) const {
    state.stack.push(state.registers[reg]);
}

REG_ARG_COMMAND(POPR)
void POPRCommand::exec(State& state) const {
    state.registers[reg] = state.stack.pop();
}

NO_ARG_COMMAND(ADD)
void ADDCommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    state.stack.push(lhs + rhs);
}

NO_ARG_COMMAND(SUB)
void SUBCommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    state.stack.push(lhs - rhs);
}

NO_ARG_COMMAND(MUL)
void MULCommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    state.stack.push(lhs * rhs);
}

NO_ARG_COMMAND(DIV)
void DIVCommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    state.stack.push(lhs / rhs);
}

NO_ARG_COMMAND(OUT)
void OUTCommand::exec(State& state) const {
    std::cout << state.stack.pop() << std::endl;
}

NO_ARG_COMMAND(IN)
void INCommand::exec(State& state) const {
    int value;
    if (std::cin >> value) {
        state.stack.push(value);
    } else {
        throw WrongInputException();
    }
}

LABEL_ARG_COMMAND(JMP)
void JMPCommand::exec(State& state) const {
    state.registers.pc_register = state.labels[label];
}

LABEL_ARG_COMMAND(JEQ)
void JEQCommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    if (lhs == rhs) {
        state.registers.pc_register = state.labels[label];
    }
}

LABEL_ARG_COMMAND(JNE)
void JNECommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    if (lhs != rhs) {
        state.registers.pc_register = state.labels[label];
    }
}

LABEL_ARG_COMMAND(JA)
void JACommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    if (lhs > rhs) {
        state.registers.pc_register = state.labels[label];
    }
}

LABEL_ARG_COMMAND(JAE)
void JAECommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    if (lhs >= rhs) {
        state.registers.pc_register = state.labels[label];
    }
}

LABEL_ARG_COMMAND(JB)
void JBCommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    if (lhs < rhs) {
        state.registers.pc_register = state.labels[label];
    }
}

LABEL_ARG_COMMAND(JBE)
void JBECommand::exec(State& state) const {
    auto rhs = state.stack.pop();
    auto lhs = state.stack.pop();
    if (lhs <= rhs) {
        state.registers.pc_register = state.labels[label];
    }
}

LABEL_ARG_COMMAND(CALL)
void CALLCommand::exec(State& state) const {
    state.call_stack.push(state.registers.pc_register);
    state.registers.pc_register = state.labels[label];
}

NO_ARG_COMMAND(RET)
void RETCommand::exec(State& state) const {
    state.registers.pc_register = state.call_stack.pop();
}

// -------------------- User-defined Commands --------------------

NO_ARG_COMMAND(DUP)
void DUPCommand::exec(State& state) const {
    auto v = state.stack.top();
    state.stack.push(v);
}

class ECHOCommand : public Command {
    public:
        ECHOCommand(const std::string& text) : text(text) {}
        ~ECHOCommand() {}

        void exec(State&) const override;

        static Command* create(const std::vector<std::string>& args) {
            std::string text;
            for (size_t i = 0; i < args.size(); ++i) {
                text += args[i];
                if (i + 1 != args.size()) {
                    text += " ";
                }
            }
            return new ECHOCommand(text);
        }

    private:
        std::string text;
};

void ECHOCommand::exec(State&) const {
    std::cout << text << std::endl;
}


static const std::unordered_map<
    std::string,
    const std::function<Command*(const std::vector<std::string>&)>
> command_create_functions = {
    // Standard commands
    {"END", COMMAND_CREATE_FUNCTION(END)},
    {"PUSH", COMMAND_CREATE_FUNCTION(PUSH)},
    {"POP", COMMAND_CREATE_FUNCTION(POP)},
    {"PUSHR", COMMAND_CREATE_FUNCTION(PUSHR)},
    {"POPR", COMMAND_CREATE_FUNCTION(POPR)},
    {"ADD", COMMAND_CREATE_FUNCTION(ADD)},
    {"SUB", COMMAND_CREATE_FUNCTION(SUB)},
    {"MUL", COMMAND_CREATE_FUNCTION(MUL)},
    {"DIV", COMMAND_CREATE_FUNCTION(DIV)},
    {"OUT", COMMAND_CREATE_FUNCTION(OUT)},
    {"IN", COMMAND_CREATE_FUNCTION(IN)},
    {"JMP", COMMAND_CREATE_FUNCTION(JMP)},
    {"JEQ", COMMAND_CREATE_FUNCTION(JEQ)},
    {"JNE", COMMAND_CREATE_FUNCTION(JNE)},
    {"JA", COMMAND_CREATE_FUNCTION(JA)},
    {"JAE", COMMAND_CREATE_FUNCTION(JAE)},
    {"JB", COMMAND_CREATE_FUNCTION(JB)},
    {"JBE", COMMAND_CREATE_FUNCTION(JBE)},
    {"CALL", COMMAND_CREATE_FUNCTION(CALL)},
    {"RET", COMMAND_CREATE_FUNCTION(RET)},

    // User defined commands
    {"DUP", COMMAND_CREATE_FUNCTION(DUP)},
    {"ECHO", COMMAND_CREATE_FUNCTION(ECHO)},
};

Command* Command::create_command(
    const std::string& command_name,
    const std::vector<std::string>& args
) {
    if (command_name == "BEGIN") {
        if (args.size() == 0) {
            return nullptr;
        } else {
            throw WrongCommandArgsException(command_name, args);
        }
    } else if (command_create_functions.count(command_name)) {
        return command_create_functions.at(command_name)(args);
    } else {
        throw UndefinedCommandException();
    }
}
