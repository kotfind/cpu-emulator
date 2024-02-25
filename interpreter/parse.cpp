#include "parse.hpp"
#include "State.hpp"
#include "Command.hpp"
#include "commands.hpp"

#include <cctype>
#include <cstring>
#include <string>
#include <vector>

bool parse_eof(const char** s) {
    return **s == 0;
}

bool parse_symbol(const char** s, char c) {
    if (**s == c) {
        ++*s;
        return true;
    }
    return false;
}

bool parse_ws(const char** s) {
    if (!isspace(**s)) {
        return false;
    }
    while (isspace(**s)) {
        ++*s;
    }
    return true;
}

bool parse_alpha(const char** s, char* c) {
    if (!isalpha(**s)) {
        return false;
    }
    *c = **s;
    ++*s;
    return true;
}

bool parse_lower(const char** s, char* c) {
    if (!islower(**s)) {
        return false;
    }
    *c = **s;
    ++*s;
    return true;
}

bool parse_upper(const char** s, char* c) {
    if (!isupper(**s)) {
        return false;
    }
    *c = **s;
    ++*s;
    return true;
}

bool parse_digit(const char** s, int* d) {
    if (!isdigit(**s)) {
        return false;
    }
    *d = **s - '0';
    ++*s;
    return true;
}

bool parse_int(const char** s, int* n) {
    const char** initial = s;

    int sgn = 1;
    if (parse_symbol(s, '-')) {
        sgn = -1;
    }
    parse_symbol(s, '+');

    int d;
    if (!parse_digit(s, &d)) {
        s = initial;
        return false;
    }

    *n = d;
    while (parse_digit(s, &d)) {
        *n = 10 * *n + d;
    }
    *n *= sgn;
    return true;
}

bool parse_lower_string(const char** s, std::string* str) {
    char c;
    if (!parse_lower(s, &c)) {
        return false;
    }

    *str = "";
    str->push_back(c);
    while (parse_lower(s, &c)) {
        str->push_back(c);
    }
    return true;
}

bool parse_label(const char** s, std::string* label_) {
    const char** initial = s;
    std::string label;
    if (!parse_lower_string(s, &label) || !parse_symbol(s, ':')) {
        s = initial;
        return false;
    }
    *label_ = label;
    return true;
}

bool parse_command_name(const char** s, std::string* command_name) {
    char c;
    if (!parse_upper(s, &c)) {
        return false;
    }
    *command_name = "";
    command_name->push_back(c);
    while (parse_upper(s, &c)) {
        command_name->push_back(c);
    }
    return true;
}

bool parse_command_arg(const char** s, std::string* arg) {
    int int_arg;
    if (parse_int(s, &int_arg)) {
        *arg = std::to_string(int_arg);
        return true;
    }

    return parse_lower_string(s, arg);
}

bool parse_command(const char** s, Command** command) {
    std::string command_name;
    if (!parse_command_name(s, &command_name)) {
        return false;
    }

    std::vector<std::string> args;
    std::string arg;
    parse_ws(s);
    while (parse_command_arg(s, &arg)) {
        args.push_back(arg);
        parse_ws(s);
    }

    *command = command_create_functions.at(command_name)(args);
    return true;
}

std::pair<Code, Labels> parse_code_file(const std::string& str) {
    Code code;
    Labels labels;

    const char* data = str.c_str();
    const char** s = &data;
    Command* command;
    std::string label;
    parse_ws(s);
    while (!parse_eof(s)) {
        if (parse_label(s, &label)) {
            labels[label] = code.size();
        } else if (parse_command(s, &command)) {
            code.push_back(command);
        } else {
            throw ParseException("EOF expected");
        }
        parse_ws(s);
    }

    return {code, labels};
}

ParseException::ParseException(const char* note) {
    error_msg += "couldn't parse";
    if (strlen(note) != 0) {
        error_msg += ":";
        error_msg += note;
    }
}

const char* ParseException::what() const noexcept {
    return error_msg.c_str();
}
