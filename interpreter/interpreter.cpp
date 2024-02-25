#include "State.hpp"
#include "commands.hpp" // TODO: delete me

int main() {
    Code code = {
        new PUSHCommand(1),
        new PUSHCommand(2),
        new ADDCommand(),
        new OUTCommand()
    };
    Labels labels = {};
    State state(code, labels);
    state.run();
}
