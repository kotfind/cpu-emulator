#pragma once

#include "Registers.hpp"
#include "Command.hpp"

#include "stack/stack.hpp"

#include <unordered_map>
#include <vector>

using Stack = stack::Stack<int>;
using CallStack = stack::Stack<size_t>;
using Code = std::vector<Command*>;
using Labels = std::unordered_map<std::string, size_t>;

class State {
    public:
        State(const Code& code, const Labels& labels);

        void run();

        Registers registers;
        Stack stack;
        CallStack call_stack;
        const Code code;
        const Labels labels;
};
