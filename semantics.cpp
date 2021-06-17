#include "semantics.hpp"
#include "SymbolTable.hpp"



Type *Num::type() const {
    return new Int();
}

Type *NumB::type() const {
    return new Byte();
}


Type *Boolean::type() const {
    return new Bool();
}

Boolean::Boolean(STYPE *e1, STYPE *e2, bool is_relop) {
    if(is_relop && is_num(e1) &&  is_num(e2))
        return;
    else if(!is_relop && is_bool(e1) &&  is_bool(e2))
        return;
    output::errorMismatch(yylineno);
}

Boolean::Boolean(STYPE *e) {
    if(is_bool(e))
        return;
    output::errorMismatch(yylineno);
}

Type *String::type() const {
    return new TypeString();
}

bool is_type(STYPE* e, string type) {
    Exp* exp=dynamic_cast<Exp*>(e);
    if(!exp)
        return false;
    auto id=dynamic_cast<Id*>(e);
    if(id)
        exp=id;
    auto t=exp->type()->name();
    return t==type;
}

bool is_num(STYPE* e){
    return is_type(e, "BYTE") || is_type(e, "INT");
}

bool is_bool(STYPE* e){
    return is_type(e, "BOOL");
}


Type *Call::type() const {
    return t;
}

Call::Call(STYPE *id_st, STYPE *el_st) {
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

void ExpList::add(STYPE *e) {
    auto exp = dynamic_cast<Exp *>(e);
    if(!exp)
        output::errorSyn(yylineno);
    Type* t =  exp->type();
    auto et = new ExpType(t, exp);
    exp_list.insert(exp_list.begin(), et);
}


vector<string> FormalsList::get_types() const {
    vector<string> argTypes;
    for(auto t:Formals)
        argTypes.emplace_back(t->type->name());
    return argTypes;}

void FormalsList::add(STYPE *var) {
    Formals.insert(Formals.begin(), dynamic_cast<Variable *>(var));
}

vector<string> Func::type_list() const {
    return formals_list->get_types();
}

string Func::name() const {
    vector<string> argTypes = type_list();
    return output::makeFunctionType(RetType->name(), argTypes);
}

const vector<Variable *> &Func::args() const {
    return formals_list->Formals;
}

void Arg::print() const {
    output::printID(var->id->name(), offset, var->type->name());
    if (var->reg) {
        int val = var->exp != nullptr ? var->exp->val : -1;
        cout << var->reg->name() << " = " << val << endl;
    }
}


