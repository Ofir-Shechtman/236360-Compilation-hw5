#include <vector>
#include <string>
#include "RegisterManager.hpp"
using namespace std;

Register *RegisterManager::alloc_reg(Variable *var) {
    auto reg = new Register(registers.size(),var);
    registers.emplace_back(reg);
    return reg;
}

string Register::name() const {
    return "t"+ to_string(id);
}

RegisterManager &RegisterManager::instance() {
    static RegisterManager inst;//only instance
    return inst;
}
