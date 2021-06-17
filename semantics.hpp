#ifndef HW5_Semantic_H
#define HW5_Semantic_H

#include "hw3_output.hpp"
#include "RegisterManager.hpp"
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

class OP : public STYPE{
public:
    string op;
    explicit OP(const string op):op(op){}
};

class Exp : public STYPE{
protected:
    explicit Exp(int val=0):val(val){}
    virtual ~Exp()=default;
public:
    int val;
    virtual Type* type() const = 0;
    virtual int getVal() const;
};

Exp* binop(STYPE* e1, STYPE* op, STYPE* e2);


class Id : public Exp{
    string id_name;
public:
    explicit Id(const string val) : id_name(val){};
    string name() const{return id_name;}
    Type* type() const override;
    int getVal() const override;
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
    explicit Boolean(bool val):Exp(val){};
    Boolean(STYPE* e1, STYPE* op, STYPE* e2, bool is_relop=false);
    explicit Boolean(STYPE* e);
    Type* type() const override;
};

class String: public STYPE{
public:
    explicit String(string val){};
    Type* type() const;
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
    Register* reg;
    Exp* exp;
    Variable(STYPE *type, STYPE *id, bool to_reg=false, STYPE* exp=nullptr) : type(dynamic_cast<Type *>(type)),
                                                          id(dynamic_cast<Id *>(id)),
                                                          reg(nullptr),
                                                          exp(dynamic_cast<Exp *>(exp)){
        if(to_reg) {
            reg = RegisterManager::instance().alloc();
        }
    }
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



class Call : public Exp{
    Type* t;
public:
    explicit Call(STYPE* id_st, STYPE* el_st=new ExpList());
    Type* type() const override;
};

#endif //HW5_Semantic_H