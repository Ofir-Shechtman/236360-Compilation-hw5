#ifndef HW5_Semantic_H
#define HW5_Semantic_H

#include "hw3_output.hpp"
#include "RegisterManager.hpp"
#include <iostream>
#include <vector>
#include "bp.hpp"

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
    virtual string reg_type() const =0;
};

class OP : public STYPE{
public:
    string op;
    explicit OP(const string op):op(op){}
};

class Exp : public STYPE{
protected:
    explicit Exp(int val=0):val(val), reg(nullptr), is_raw(true){}
    virtual ~Exp()=default;
public:
    int val;
    bool is_raw;
    Register* reg;
    virtual Type* type() const = 0;
    virtual string get(bool full_const=true) const;
};

Exp* binop(STYPE* e1, STYPE* op, STYPE* e2);


class Id : public Exp{
    string id_name;
public:
    explicit Id(const string val);
    string name() const{return id_name;}
    Type* type() const override;
    string get(bool full_const=true) const override;
    void run_bool_check();
};
bool is_type(STYPE* e, string type) ;

bool is_num(STYPE* e);
bool is_bool(STYPE* e);


class Num : public Exp{
public:
    explicit Num(const string val) : Exp(stoi(val)){};
    Type* type() const override;
};

class NumB : public Exp{
public:
    explicit NumB(const string name):Exp(stoi(name)){
        if(val>255)
            output::errorByteTooLarge(yylineno, name);
    };
    explicit NumB(const int val) : NumB(to_string(val)){};
    Type* type() const override;
};

class Boolean : public Exp{
public:
    BooleanE data;
    Boolean(Id* id);
    explicit Boolean(bool val, bool br=true);;
    Boolean(STYPE* e1, STYPE* op, STYPE* e2);
    Boolean(STYPE* e1, STYPE* op, STYPE* m, STYPE* e2);
    explicit Boolean(STYPE* e);
    Type* type() const override;
};

class String: public Exp{
    string str;
    string const_name;
public:
    explicit String(string val);;
    Type* type() const;
    string get(bool full_const=true) const override;
};


class Int : public Type{
public:
    Int()=default;
    string name() const override {return "INT";};
    string reg_type() const  override {return "i32";}
};

class Byte : public Type{
public:
    Byte()=default;
    string name() const override {return "BYTE";};
    string reg_type() const  override {return "i32";}
};

class Void : public Type{
public:
    Void()=default;
    string name() const override {return "VOID";};
    string reg_type() const  override {return "void";}
};

class TypeString : public Type{
public:
    TypeString()=default;
    string name() const override {return "STRING";};
    string reg_type() const  override {return "not supported";}
};

class Bool : public Type{
public:
    Bool()=default;
    string name() const override {return "BOOL";};
    string reg_type() const  override {return "i1";}
};

class Variable : public  STYPE{
public:
    Type* type;
    Id* id;
    Exp* exp;
    Variable(STYPE *type, STYPE *id, STYPE* exp=nullptr);
};

struct ExpType : public STYPE{
    Type* type;
    Exp* exp;
    ExpType(Exp* e);;
};

class ExpList : public STYPE{
    static ExpList* temp_name;
public:
    vector<ExpType*> exp_list;
    ExpList()=default;
    void add(ExpType* e);
    void add(STYPE* e){add(dynamic_cast<ExpType*>(e));}
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
    string reg_type() const  override {return "not supported";}
};

class ReturnType : public Type{
    string t;
public:
    ReturnType(string t): t(t){};
    string name() const override{
        return t;
    }
    string reg_type() const  override {return "not supported";}
};



struct Arg{
    Variable* var;
    int offset;
    //Arg(STYPE* v, int offset): var((Variable*)v), offset(offset){};
    Arg(Variable* v, int offset):var(v), offset(offset){};
    void print() const;
    string ptr_name() const;
};



class Call : public Exp{
    Type* t;
public:
    explicit Call(STYPE* id_st, STYPE* el_st=new ExpList());
    Type* type() const override;
};

#endif //HW5_Semantic_H