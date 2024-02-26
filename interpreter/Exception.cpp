#include "Exception.hpp"

Exception::Exception(const std::string& err) : error_msg("error: " + err) {}

Exception::Exception() : error_msg("error") {}

const char* Exception::what() const noexcept {
    return error_msg.c_str();
}
