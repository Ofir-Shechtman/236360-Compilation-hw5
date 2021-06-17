#ifndef HW5_Semantic_H
#define HW5_Semantic_H

#endif //HW5_Semantic_H
#include "hw3_output.hpp"
#include <iostream>
#include <vector>

using namespace std;

class STYPE {
protected:
    STYPE()=default;
    virtual ~STYPE()=default;
};
#ifndef YYSTYPE
#define YYSTYPE STYPE*
#endif


class Type : public STYPE{
protected:
    Type()=default;
    virtual ~Type()=default;
public:
    virtual string name() const =0;
};

class Exp : public STYPE{
protected:
    Exp()=default;
    virtual ~Exp()=default;
public:
    virtual Type* type() const = 0;
};

class Id : public Exp{
    string id_name;
public:
    explicit Id(const string val) : id_name(val){};
    string name() const{return id_name;}
    Type* type() const override;
};
bool is_type(STYPE* e, string type) ;

bool is_num(STYPE* e);
bool is_bool(STYPE* e);


class Num : public Exp{
public:
    int val;
    explicit Num(const string name) : val(stoi(name)){};
    Type* type() const override;
};

class NumB : public Exp{
public:
    int val;
    explicit NumB(const string name);;
    explicit NumB(const int val) : NumB(to_string(val)){};
    Type* type() const override;
};

class Boolean : public Exp{
public:
    explicit Boolean(){};
    Boolean(STYPE* e1, STYPE* e2, bool is_relop=false);
    explicit Boolean(STYPE* e);
    Type* type() const override;
};

class String : public Exp{
    string val;
public:
    explicit String(string val) : val(val){};
    Type* type() const override;
};


class Int : public Type{
public:
    Int()=default;
    string name() const override {return "INT";};
};

class Byte : public Type{
public:
    Byte()=default;
    string name() const override {return "BYTE";};
};

class Void : public Type{
public:
    Void()=default;
    string name() const override {return "VOID";};
};

class TypeString : public Type{
public:
    TypeString()=default;
    string name() const override {return "STRING";};
};

class Bool : public Type{
public:
    Bool()=default;
    string name() const override {return "BOOL";};
};

class Variable : public  STYPE{
public:
    Type* type;
    Id* id;
    Variable(STYPE* type, STYPE* id): type(dynamic_cast<Type *>(type)), id(dynamic_cast<Id *>(id)){};
};

struct ExpType{
    Type* type;
    Exp* exp;
    ExpType(Type* t, Exp* e):type(t), exp(e){};
};

class ExpList : public STYPE{
    static ExpList* temp_name;
public:
    vector<ExpType*> exp_list;
    ExpList()=default;
    void add(STYPE* e);;
};


class FormalsList : public STYPE{
public:
    vector<Variable*> Formals;
    FormalsList()=default;
    void add(STYPE* var);;
    vector<string> get_types() const;;
};


class Func : public Type{
    FormalsList* formals_list;
public:
    Type* RetType;
    Func(STYPE* p, STYPE* f):formals_list(dynamic_cast<FormalsList *>(f)),  RetType(dynamic_cast<Type *>(p)){}
    vector<string> type_list() const;
    string name() const override;
    const vector<Variable*>& args() const;
};

class ReturnType : public Type{
    string t;
public:
    ReturnType(string t): t(t){};
    string name() const override{
        return t;
    }
};


struct Arg{
    Variable* var;
    int offset;
    //Arg(STYPE* v, int offset): var((Variable*)v), offset(offset){};
    Arg(Variable* v, int offset):var(v), offset(offset){};
    void print() const;
};

class SymbolTable{
    vector<vector<Arg>> tables_stack;
    vector<int> offsets_stack;
    vector<Arg> funcs;
    Type* cur_return;
    int in_while;
    bool in_switch;
    static SymbolTable* singleton_;
    SymbolTable();;

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

    bool contain_var(const string& name) const;

    Func* get_func_type(const Id* id) const;

    bool contain_func(const string& name) const;

    void assign(STYPE* id_st, STYPE* exp_st);

    void check_return(STYPE* t);

    void check_while(STYPE* t) const;
};


class Call : public Exp{
    Type* t;
public:
    explicit Call(STYPE* id_st, STYPE* el_st=new ExpList());
    Type* type() const override;
};