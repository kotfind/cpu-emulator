#pragma once

#include "Command.hpp"
#include "Registers.hpp"
#include "Labels.hpp"
#include "commands_defines.hpp"
#include "Exception.hpp"

#include <exception>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class WrongCommandArgsException : public Exception {
    public:
        WrongCommandArgsException(
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
};

class WrongInputException : public Exception {
    public:
        WrongInputException() : Exception("wrong input") {}
};

// Standard commands
NO_ARG_COMMAND(END)
INT_ARG_COMMAND(PUSH)
NO_ARG_COMMAND(POP)
REG_ARG_COMMAND(PUSHR)
REG_ARG_COMMAND(POPR)
NO_ARG_COMMAND(ADD)
NO_ARG_COMMAND(SUB)
NO_ARG_COMMAND(MUL)
NO_ARG_COMMAND(DIV)
NO_ARG_COMMAND(OUT)
NO_ARG_COMMAND(IN)
LABEL_ARG_COMMAND(JMP)
LABEL_ARG_COMMAND(JEQ)
LABEL_ARG_COMMAND(JNE)
LABEL_ARG_COMMAND(JA)
LABEL_ARG_COMMAND(JAE)
LABEL_ARG_COMMAND(JB)
LABEL_ARG_COMMAND(JBE)
LABEL_ARG_COMMAND(CALL)
NO_ARG_COMMAND(RET)

// User-defined commands
NO_ARG_COMMAND(DUP)

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

const std::unordered_map<
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
