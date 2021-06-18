//
// Created by ofir5 on 18/06/21.
//

#include "llvm_funcs.hpp"

using namespace std;

stringstream alloca_base(const string &ptr_name) {
    //%arr = alloca i32, i32 %size
    stringstream res;
    res<<"\t"<<ptr_name << " = alloca i32, ";
    return res;
}

string get_alloca(const string& ptr_name, const string &reg_name, const string & id_name){
    //%arr = alloca i32, i32 %size
    stringstream res=alloca_base(ptr_name);
    res<< reg_name << "\t\t; " << id_name;
    return res.str();
}



string define(const string &func_name, int num_arg, bool is_void) {
    //define i32 @add_3_numbers(i32, i32, i32) {
    stringstream res;
    string type = is_void ? "void" : "i32";
    res<<"define " << type <<" @" << func_name << "(";
    for(int i=0;i<num_arg-1;++i){
        res << "i32, ";
    }
    if(num_arg)
        res << "i32";
    res <<") {";
    return res.str();
}

string ret(const string &reg_name) {
    //ret i32 %6
    stringstream res;
    res<<"\tret "<<reg_name;
    return res.str();
}
string ret_void() {
    return "\tret void";
}

string get_binop(const string& reg_name, const string& op, const string& l, const string& r) {
    //%size = add i32 10, 0
    stringstream res;
    res<<"\t"<<reg_name << " = " << op << " " << l << ", " << r;
    return res.str();
}

string load(const string& reg_name, const string& type, const string& ptr) {
    //%val = load i32, i32* %ptr
    stringstream res;
    res<<"\t"<<reg_name << " = load " << type << ", " << "i32* " << ptr;
    return res.str();
}

string store(const string& reg_name, const string& ptr) {
    //store i32 3, i32* %ptr
    stringstream res;
    res<<"\tstore "<<reg_name <<  ", " << "i32* " << ptr;
    return res.str();
}



