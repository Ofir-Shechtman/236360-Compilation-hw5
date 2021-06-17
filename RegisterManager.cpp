#include <vector>
#include <string>
#include "RegisterManager.hpp"
using namespace std;

Register *RegisterManager::alloc() {
    auto reg = new Register(register_count++);
    return reg;
}

string Register::name() const {
    return "%t"+ to_string(id);
}


RegisterManager &RegisterManager::instance() {
    static RegisterManager inst;//only instance
    return inst;
}


