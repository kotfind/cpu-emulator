#pragma once

#include "interpreter/Registers.hpp"
#include "stack/stack.hpp"
#include <unordered_map>
#include <vector>

class Command;

using Stack = stack::Stack<int>;
using CallStack = stack::Stack<size_t>;
using Code = std::vector<Command>;
using Labels = std::unordered_map<std::string, size_t>;

struct State {
    Registers registers;
    Stack stack;
    CallStack call_stack;
    const Code code;
    const Labels labels;
};
