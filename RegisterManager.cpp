#include <vector>
#include <string>
#include "RegisterManager.hpp"
using namespace std;

Register *RegisterManager::alloc(int bit_num, bool is_arg) {
    auto reg = new Register(register_count++, bit_num, is_arg);
    return reg;
}

string Register::full_name() const {
    return type()+" "+ name();
}

string Register::name() const {
    string t = is_arg ? "" : "t";
    return "%"+t+ to_string(id);
}

string Register::type() const {
    return "i"+to_string(bit_num);
}


RegisterManager &RegisterManager::instance() {
    static RegisterManager inst;//only instance
    return inst;
}

void RegisterManager::reset() {
    register_count=0;

}


