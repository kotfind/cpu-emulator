#pragma once

#include "Exception.hpp"

#include <string>
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

class UndefinedCommandException : public Exception {
    public:
        UndefinedCommandException()
          : Exception("undefined command")
        {}
};

class WrongInputException : public Exception {
    public:
        WrongInputException() : Exception("wrong input") {}
};

class State;

class Command {
    public:
        virtual ~Command() {}

        virtual void exec(State&) const = 0;

        // Returns:
        // * nullptr for BEGIN command
        // * pointer to Command for other commands
        static Command* create_command(
            const std::string& command_name,
            const std::vector<std::string>& args
        );
};
