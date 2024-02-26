#pragma once

#include "State.hpp"
#include "Labels.hpp"

#include <exception>
#include <utility>

std::pair<Code, Labels> parse_code_file(const std::string&);

class ParseException : public std::exception {
    public:
        ParseException(const char* note);

        const char* what() const noexcept override;

    private:
        std::string error_msg;
};
