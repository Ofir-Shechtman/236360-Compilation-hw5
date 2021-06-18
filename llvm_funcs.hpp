//
// Created by ofir5 on 18/06/21.
//

#ifndef HW5_LLVM_FUNCS_H
#define HW5_LLVM_FUNCS_H
#include <string>
#include <sstream>
using namespace std;


stringstream alloca_base(const string &ptr_name);
string get_alloca(const string& ptr_name, const string &reg_name, const string& id_name);
string define(const string &func_name, int num_arg, bool is_void);
string get_binop(const string& reg_name, const string& op, const string& l, const string& r);
string load(const string& reg_name, const string& type, const string& ptr);
string store(const string& reg_name, const string& ptr);
string ret(const string& reg_name);
string ret_void();


#endif //HW5_LLVM_FUNCS_H
