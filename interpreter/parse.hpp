#pragma once

#include "State.hpp"
#include "Labels.hpp"
#include "Exception.hpp"

#include <utility>

std::pair<Code, Labels> parse_code_file(const std::string&);

class EOFExpectedException : public Exception {
    public:
        EOFExpectedException()
          : Exception("EOF expected")
        {}
};
