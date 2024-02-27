#include "parse.hpp"
#include "State.hpp"
#include "Command.hpp"
#include "Labels.hpp"

#include <cctype>
#include <cstring>
#include <iostream>
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

bool parse_comment(const char** s) {
    if (!parse_symbol(s, ';')) {
        return false;
    }

    while (**s != 0 && **s != '\n') {
        ++*s;
    }

    return true;
}

// parses comments and whitespaces
bool parse_cws(const char** s) {
    bool parsed_any = false;

    if (parse_ws(s)) {
        parsed_any = true;
    }
    while (parse_comment(s)) {
        parsed_any = true;
        parse_ws(s);
    }

    return parsed_any;
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

bool parse_lower_or_underscore(const char** s, char* c) {
    if (!islower(**s) && **s != '_') {
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
    const char* initial = *s;

    int sgn = 1;
    if (parse_symbol(s, '-')) {
        sgn = -1;
    }
    parse_symbol(s, '+');

    int d;
    if (!parse_digit(s, &d)) {
        *s = initial;
        return false;
    }

    *n = d;
    while (parse_digit(s, &d)) {
        *n = 10 * *n + d;
    }
    *n *= sgn;
    return true;
}

bool parse_lower_or_underscore_string(const char** s, std::string* str) {
    char c;
    if (!parse_lower_or_underscore(s, &c)) {
        return false;
    }

    *str = "";
    str->push_back(c);
    while (parse_lower_or_underscore(s, &c)) {
        str->push_back(c);
    }
    return true;
}

bool parse_label_name(const char** s, LabelName* label_) {
    const char* initial = *s;
    std::string label;
    if (!parse_lower_or_underscore_string(s, &label) || !parse_symbol(s, ':')) {
        *s = initial;
        return false;
    }
    *label_ = LabelName(label);
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
    const char* initial = *s;

    int int_arg;
    if (parse_int(s, &int_arg)) {
        *arg = std::to_string(int_arg);
        return true;
    }

    std::string str;
    if (!parse_lower_or_underscore_string(s, &str) || parse_symbol(s, ':')) {
        *s = initial;
        return false;
    }

    *arg = str;
    return true;
}

bool parse_command(const char** s, Command** command) {
    std::string command_name;
    if (!parse_command_name(s, &command_name)) {
        return false;
    }
    std::vector<std::string> args;
    std::string arg;
    parse_cws(s);
    while (parse_command_arg(s, &arg)) {
        args.push_back(arg);
        parse_cws(s);
    }

    *command = Command::create_command(command_name, args);
    return true;
}

std::pair<Code, Labels> parse_code_file(const std::string& str) {
    Code code;
    Labels labels;

    const char* data = str.c_str();
    const char** s = &data;
    Command* command;
    LabelName label("");
    parse_cws(s);
    while (!parse_eof(s)) {
        if (parse_label_name(s, &label)) {
            labels.insert(label, code.size());
        } else if (parse_command(s, &command)) {
            if (command == nullptr /* BEGIN command */) {
                labels.insert(LabelName::BEGIN_LABEL, code.size());
                delete command;
            } else {
                code.push_back(command);
            }
        } else {
            throw EOFExpectedException();
        }
        parse_cws(s);
    }

    if (!labels.contains(LabelName::BEGIN_LABEL)) {
        labels.insert(LabelName::BEGIN_LABEL, 0);
    }

    return {code, labels};
}
