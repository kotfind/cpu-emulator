#pragma once

#include "Exception.hpp"
#include <cstddef>
#include <string>

class UndefinedRegisterException : public Exception {
    public:
        UndefinedRegisterException(const std::string& reg_name)
          : Exception("no register called: " + reg_name)
        {}
};

class Registers;

class RegisterName {
    public:
        RegisterName(const std::string& reg);

    private:
        // if pc_register == true than it's pc_register
        // otherwise it's general register number reg_num

        bool pc_register;
        size_t reg_num;

    friend Registers;
};

class Registers {
    public:
        Registers();

        int& operator[](const RegisterName& reg_name);
        int operator[](const RegisterName& reg_name) const;

        static constexpr size_t REGISTERS_NUMBER = 4;
        static_assert(REGISTERS_NUMBER <= 26);

        int general_reisters[REGISTERS_NUMBER];
        int pc_register;

    friend RegisterName;
};
