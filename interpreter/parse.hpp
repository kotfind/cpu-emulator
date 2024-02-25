#pragma once

#include "State.hpp"

#include <exception>
#include <utility>

std::pair<Code, Labels> parse_code_file(const std::string&);

class ParseException : public std::exception {
    public:
        ParseException(const char* note);

        const char* what();

    private:
        std::string error_msg;
};
