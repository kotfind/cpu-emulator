#pragma once

class State;

class Command {
    public:
        virtual ~Command() {}

        virtual void exec(State&) const = 0;
};
