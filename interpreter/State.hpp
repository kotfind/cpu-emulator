#pragma once

#include "Registers.hpp"
#include "Command.hpp"
#include "Labels.hpp"

#include "stack/stack.hpp"

#include <unordered_map>
#include <vector>

using Stack = stack::Stack<int>;
using CallStack = stack::Stack<size_t>;
using Code = std::vector<Command*>;

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
