#include "Registers.hpp"

// -------------------- UndefinedRegisterException --------------------

UndefinedRegisterException::UndefinedRegisterException(const std::string& reg_name) {
    error_msg = "no register called: ";
    error_msg += reg_name;
}

const char* UndefinedRegisterException::what() {
    return error_msg.c_str();
}

// -------------------- RegisterName --------------------

RegisterName::RegisterName(const std::string& reg) {
    if (reg == "PC") {
        pc_register = true;
        return;
    }

    if (reg.length() == 2 && reg[1] == 'X') {
        int idx = reg[0] - 'A';
        if (idx >= 0 && idx < Registers::REGISTERS_NUMBER) {
            pc_register = false;
            reg_num = idx;
        }
    }

    throw UndefinedRegisterException(reg);
}

// -------------------- Registers --------------------

Registers::Registers() {
    for (size_t i = 0; i < REGISTERS_NUMBER; ++i) {
        general_reisters[i] = 0;
    }
    pc_register = 0;
}

int Registers::operator[](const RegisterName& reg_name) const {
    return reg_name.pc_register
        ? pc_register
        : general_reisters[reg_name.reg_num];
}

int& Registers::operator[](const RegisterName& reg_name) {
    return reg_name.pc_register
        ? pc_register
        : general_reisters[reg_name.reg_num];
}
