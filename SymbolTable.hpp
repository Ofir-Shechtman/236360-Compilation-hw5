#ifndef H_SymbolTable
#define H_SymbolTable

#include "semantics.hpp"
#include <iostream>
#include <vector>

using namespace std;

class SymbolTable{
    vector<vector<Arg>> tables_stack;
    vector<int> offsets_stack;
    vector<Arg> funcs;
    Type* cur_return;
    int in_while;
    bool in_switch;
    static SymbolTable* singleton_;
    SymbolTable();;
    Variable* get_id_variable(const Id* id) const;

public:
    ~SymbolTable(){
        print_funcs();
    }
    void print_funcs() const;
    void operator=(const SymbolTable &) = delete;
    static SymbolTable *GetInstance();
    void push();

    void push_ret(STYPE* rt);

    void push_while(STYPE* rt);

    void pop();

    void pop_while();

    void enter_switch();

    void exit_switch(){
        in_switch=false;
    }

    void add_Func(STYPE* f);
    void add_Func(Variable* f);

    void add_var(Variable* v, int offset);
    void add_var(STYPE* v);

    Type* get_id_type(const Id* id) const;

    Exp* get_id_val(const Id* id) const;

    bool contain_var(const string& name) const;

    Func* get_func_type(const Id* id) const;

    bool contain_func(const string& name) const;

    void assign(STYPE* id_st, STYPE* exp_st);

    void check_return(STYPE* t);

    void check_while(STYPE* t) const;
};

#endif //H_SymbolTable