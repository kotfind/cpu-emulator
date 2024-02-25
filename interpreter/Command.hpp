#pragma once

#include "State.hpp"

class Command {
    public:
        virtual ~Command() {}

        virtual void exec(State& state) const = 0;
};
