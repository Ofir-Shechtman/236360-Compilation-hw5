//
// Created by ofir5 on 18/06/21.
//

#include "llvm_funcs.hpp"

using namespace std;


string get_alloca(const string& ptr_name, const string &reg_name, const string & type, const string & id_name){
    //%arr = alloca i32, i32 %size
    stringstream res;
    res << "\t"<<ptr_name << " = alloca "<<type<<", ";
    res<< reg_name;
    while(res.str().size()<33){
        res << " ";
    }
    res << ";" <<id_name;
    return res.str();
}


string define(const string &func_name, const vector<string>& arg_type, const string & type) {
    //define i32 @add_3_numbers(i32, i32, i32) {
    stringstream res;
    res<<"define " << type <<" @" << func_name << "(";
    if(!arg_type.empty()) {
        for (int i = 0; i < arg_type.size() - 1; ++i) {
            res << arg_type[i] << ", ";
        }
        res << arg_type[arg_type.size() - 1];
    }
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
    res<<"\t"<<reg_name << " = load " << type << ", " << type << "* " << ptr;
    return res.str();
}

string store(const string& reg_name, const string& type, const string& ptr) {
    //store i32 3, i32* %ptr
    stringstream res;
    res<<"\tstore "<<reg_name <<  ", " << type << "* " << ptr;
    return res.str();
}

string br_uncond(string label) {
    if(label!="@")
        label = "%"+label;
    return "\tbr label " + label;
}

string br_cond(const string& reg_name, string label_true,
               string label_false) {
    //br i1 %b, label %then, label %else
    if(label_true!="@")
        label_true = "%"+label_true;
    if(label_false!="@")
        label_false = "%"+label_false;
    return "\tbr " + reg_name + ", label " +label_true + ", label " + label_false;
}

string phi(const string &ptr, const string& type, vector<pair<string, string>> pairs) {
    //%to_print = phi i8* [%even_str, %even_label], [%odd_str, %odd_label]
    stringstream res;
    res<<"\t"<<ptr << " = phi " << type << "* ";
    for (int i = 0; i < pairs.size(); ++i) {
        //[%odd_str, %odd_label],
        res << "["<< pairs[i].first << ", " << pairs[i].second <<"]";
        if(i!=pairs.size()-1)
            res <<  ", ";
    }
    return res.str();


}

string
call_void(const string &type, const string &func_name, const vector<string> &args) {
    //%v1 = call i32 @add_3_numbers(i32 1, i32 10, i32 11)
    stringstream res;
    res << "call " << type << " @"<<func_name << "(";
    if(!args.empty()) {
        for (int i = 0; i < args.size() - 1; ++i) {
            res << args[i] << ", ";
        }
        res << args[args.size() - 1];
    }
    res <<")";
    return res.str();
}





string
call(const string &reg_name, const string &type, const string &func_name,
     const vector<string> &args) {
    //%v1 = call i32 @add_3_numbers(i32 1, i32 10, i32 11)
    stringstream res;
    res << "\t"<< reg_name << " = " << call_void(type, func_name, args);
    return res.str();
}

string
internal_const(const string &reg_name, int len, const string &the_string) {
    //@.even_str = internal constant [6 x i8] c"even\0A\00"
    stringstream res;
    res << "@." << reg_name << " = constant ["<<len+2<<" x i8] c\""<<the_string<<"\\0A\\00\"";
    return res.str();
}

string
getelementptr(const string &reg_name, int size, const string &const_name) {
//%spec_ptr = getelementptr [4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0
    stringstream res;
    res << "\t"<< reg_name << " = getelementptr ["<<size<<" x i8], [ "<<size<<" x i8]* @."<<const_name<<", i32 0, i32 0";
    return res.str();
}


