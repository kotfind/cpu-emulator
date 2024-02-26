#pragma once

#include <exception>
#include <string>

class Exception : public std::exception {
    public:
        Exception(const std::string&);
        Exception();

        const char* what() const noexcept override;

    protected:
        std::string error_msg;
};
