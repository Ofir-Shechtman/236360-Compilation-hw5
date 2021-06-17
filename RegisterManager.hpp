#ifndef HW5_REGISTERMANAGER_H
#define HW5_REGISTERMANAGER_H

#endif //HW5_REGISTERMANAGER_H
#include "semantics.hpp"
using namespace std;

struct Register{
    unsigned int id;
    string name() const;
    Variable* var;
    Register(unsigned int id, Variable* var):id(id), var(var){}
};

class RegisterManager {
    RegisterManager() = default;
    vector<Register*> registers;
public:
    RegisterManager(RegisterManager const &) = delete;
    void operator=(RegisterManager const &) = delete;
    static RegisterManager &instance();
    Register* alloc_reg(Variable* var);
};