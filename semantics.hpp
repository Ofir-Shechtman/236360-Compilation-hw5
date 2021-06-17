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
    explicit NumB(const string name) : val(stoi(name)){
        if(val>255)
            output::errorByteTooLarge(yylineno, name);
    };
    explicit NumB(const int val) : NumB(to_string(val)){};
    Type* type() const override;
};

class Boolean : public Exp{
public:
    explicit Boolean(){};
    Boolean(STYPE* e1, STYPE* e2, bool is_relop=false){
        if(is_relop && is_num(e1) &&  is_num(e2))
            return;
        else if(!is_relop && is_bool(e1) &&  is_bool(e2))
            return;
        output::errorMismatch(yylineno);
    }
    explicit Boolean(STYPE* e){
        if(is_bool(e))
            return;
        output::errorMismatch(yylineno);
    }
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
    void add(STYPE* e){
        auto exp = dynamic_cast<Exp *>(e);
        if(!exp)
            output::errorSyn(yylineno);
        Type* t =  exp->type();
        auto et = new ExpType(t, exp);
        exp_list.insert(exp_list.begin(), et);
    };
};


class FormalsList : public STYPE{
public:
    vector<Variable*> Formals;
    FormalsList()=default;
    void add(STYPE* var){
        Formals.insert(Formals.begin(), dynamic_cast<Variable *>(var));
    };
    vector<string> get_types() const{
        vector<string> argTypes;
        for(auto t:Formals)
            argTypes.emplace_back(t->type->name());
        return argTypes;};
};


class Func : public Type{
    FormalsList* formals_list;
public:
    Type* RetType;
    Func(STYPE* p, STYPE* f):formals_list(dynamic_cast<FormalsList *>(f)),  RetType(dynamic_cast<Type *>(p)){}
    vector<string> type_list() const{
        return formals_list->get_types();
    }
    string name() const override{
        vector<string> argTypes = type_list();
        return output::makeFunctionType(RetType->name(), argTypes);
    }
    const vector<Variable*>& args() const{
        return formals_list->Formals;
    }
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
    void print() const {
        output::printID(var->id->name(), offset,var->type->name());
    }
};

class SymbolTable{
    vector<vector<Arg>> tables_stack;
    vector<int> offsets_stack;
    vector<Arg> funcs;
    Type* cur_return;
    int in_while;
    bool in_switch;
    static SymbolTable* singleton_;
    SymbolTable(){
        auto fl1= new FormalsList();
        fl1->add(new Variable(new TypeString(), new Id("arg")));
        Func* f1= new Func(new Void(), fl1);
        auto* v1 = new Variable(f1, new Id("print"));

        auto fl2= new FormalsList();
        fl2->add(new Variable(new Int(), new Id("arg")));
        Func* f2= new Func(new Void(), fl2);
        auto* v2 = new Variable(f2, new Id("printi"));

        funcs={Arg(v1, 0), Arg(v2, 0)};
        tables_stack.emplace_back(funcs);
        offsets_stack.emplace_back(-1);
        cur_return = nullptr;
        in_while=0;
        in_switch=false;

    };

public:
    ~SymbolTable(){
        print_funcs();
    }
    void print_funcs() const {
        //if(funcs.size()<=2) return;
        bool MainMissing = true;
        for(auto f:funcs){
            if(f.var->id->name()=="main" && f.var->type->name()=="()->VOID") {
                MainMissing= false;
            }
        }
        if(MainMissing) output::errorMainMissing();
        output::endScope();
        for(auto f:funcs){
            f.print();
        }

    }
    void operator=(const SymbolTable &) = delete;
    static SymbolTable *GetInstance();
    void push(){
        tables_stack.emplace_back(vector<Arg>());
        offsets_stack.emplace_back(offsets_stack.back());

    }

    void push_ret(STYPE* rt){
        push();
        cur_return = dynamic_cast<Type *>(rt);
    }

    void push_while(STYPE* rt){
        push();
        in_while++;
    }

    void pop(){
        output::endScope();
        for(auto a:tables_stack.back()){
            a.print();
        }
        tables_stack.pop_back();
        offsets_stack.pop_back();
    }

    void pop_while(){
        pop();
        in_while--;
    }

    void enter_switch(){
        in_switch=true;
    }

    void exit_switch(){
        in_switch=false;
    }

    void add_Func(STYPE* f){
        add_Func(dynamic_cast<Variable *>(f));
    }
    void add_Func(Variable* f){
        if(contain_var(f->id->name()) || contain_func(f->id->name()))
            output::errorDef(yylineno, f->id->name());
//        if(f->id->name()=="main" && f->type->name()!="()->VOID")
//            output::errorMainMissing();
        auto args=  dynamic_cast<Func *>(f->type)->args();
        funcs.emplace_back(Arg(f, 0));
        int offset=-1;
        for(auto a:args){
            add_var(a, offset--);
        }
    }

    void add_var(Variable* v, int offset){
        if(contain_var(v->id->name()) || contain_func(v->id->name()))
            output::errorDef(yylineno, v->id->name());
        Arg new_arg = Arg(dynamic_cast<Variable *>(v), offset);
        tables_stack.back().emplace_back(new_arg);
    }
    void add_var(STYPE* v){
        add_var(dynamic_cast<Variable *>(v),  ++offsets_stack.back());
    }

    Type* get_id_type(const Id* id) const{
        for(const auto& i:tables_stack){
            for(auto j : i){
                if(j.var->id->name()==id->name())
                    return j.var->type;
            }
        }
        return nullptr;
    }

    bool contain_var(const string& name) const{
        auto id = Id(name);
        auto t = get_id_type(&id);
        return t != nullptr;
    }

    Func* get_func_type(const Id* id) const{
        for(const auto& i:funcs){
            if(i.var->id->name()==id->name())
                return dynamic_cast<Func *>(i.var->type);
        }
        return nullptr;
    }

    bool contain_func(const string& name) const{
        auto id = Id(name);
        auto t = get_func_type(&id);
        return t != nullptr;
    }

    void assign(STYPE* id_st, STYPE* exp_st){
        Id* id = dynamic_cast<Id *>(id_st);
        Type* exp_type = dynamic_cast<Exp *>(exp_st)->type();
        if(!contain_var(id->name()))
            output::errorUndef(yylineno, id->name());
        auto id_t = get_id_type(id);
        if(id_t->name() == exp_type->name() || (id_t->name() == "INT" && exp_type->name() == "BYTE"))
            return;
        else
            output::errorMismatch(yylineno);
    }

    void check_return(STYPE* t){
        if(dynamic_cast<Void *>(t)){
            if(!dynamic_cast<Void *>(cur_return)) {
                output::errorMismatch(yylineno);
            }
        }
        else{
            Type *ret = (dynamic_cast<Exp *>(t))->type();
            if(ret->name()!=cur_return->name() && !(cur_return->name()=="INT" && ret->name()=="BYTE"))
                output::errorMismatch(yylineno);
        }

    }

    void check_while(STYPE* t){
        Type *ret = (dynamic_cast<ReturnType *>(t));
        if(in_switch) {
            if (ret->name() == "continue")
                output::errorUnexpectedContinue(yylineno);
        }
        else if(!in_while) {
            if(ret->name()=="break")
                    output::errorUnexpectedBreak(yylineno);
            else if(ret->name()=="continue")
                output::errorUnexpectedContinue(yylineno);
        }
    }
};


class Call : public Exp{
    Type* t;
public:
    Call(STYPE* id_st, STYPE* el_st=new ExpList()){
        SymbolTable* st = SymbolTable::GetInstance();
        Id* id = dynamic_cast<Id *>(id_st);
        auto* el = dynamic_cast<ExpList *>(el_st);
        if(!st->contain_func(id->name()))
            output::errorUndefFunc(yylineno,id->name());
        auto f_args = st->get_func_type(id)->type_list();
        auto& exp_list = el->exp_list;
        if(f_args.size()!=exp_list.size())
            output::errorPrototypeMismatch(yylineno, id->name(), f_args);
        auto it1=f_args.begin();
        auto it2=exp_list.begin();
        for(;it1!=f_args.end(); ++it1,++it2){
            if((*it1)!=(*it2)->type->name()  && !((*it1)=="INT" && (*it2)->type->name()=="BYTE"))
                output::errorPrototypeMismatch(yylineno, id->name(), f_args);
        }
        t= dynamic_cast<Func *>(st->get_func_type(id))->RetType;
    }
    Type* type() const override{
        return t;
    }
};