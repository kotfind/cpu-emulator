#pragma once

#include "Command.hpp"
#include "interpreter/Registers.hpp"
#include "interpreter/commands_defines.hpp"

#include <exception>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class WrongCommandArgsException : public std::exception {
    public:
        WrongCommandArgsException(const std::string& command_name, const std::vector<std::string>& args);

        const char* what();

    private:
        std::string error_msg;
};

NO_ARG_COMMAND(BEGIN)
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

const std::unordered_map<
    std::string,
    const std::function<Command*(const std::vector<std::string>&)>
> command_create_functions = {
    {"BEGIN", COMMAND_CREATE_FUNCTION(BEGIN)},
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
};
