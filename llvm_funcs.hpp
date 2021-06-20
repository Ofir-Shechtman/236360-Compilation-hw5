//
// Created by ofir5 on 18/06/21.
//

#ifndef HW5_LLVM_FUNCS_H
#define HW5_LLVM_FUNCS_H
#include <string>
#include <sstream>
#include <vector>
using namespace std;


string get_alloca(const string& ptr_name, const string &reg_name, const string & type, const string& id_name);
string define(const string &func_name, const vector<string>& arg_type, const string & type);
string get_binop(const string& reg_name, const string& op, const string& l, const string& r);
string load(const string& reg_name, const string& type, const string& ptr);
string store(const string& reg_name, const string& type, const string& ptr);
string ret(const string& reg_name);
string ret_void();
string br_uncond(const string& label);
string br_cond(const string& reg_name, const string& label_true, const string& label_false);
string phi(const string& ptr, const string& type, vector<pair<string, string>> pairs);

#endif //HW5_LLVM_FUNCS_H
