#include "semantics.hpp"

SymbolTable* SymbolTable::singleton_= nullptr;

SymbolTable *SymbolTable::GetInstance() {
    if(singleton_==nullptr){
        singleton_ = new SymbolTable();
    }
    return singleton_;
}

SymbolTable::SymbolTable() {
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

}

void SymbolTable::print_funcs() const {
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

void SymbolTable::push() {
    tables_stack.emplace_back(vector<Arg>());
    offsets_stack.emplace_back(offsets_stack.back());

}

void SymbolTable::push_ret(STYPE *rt) {
    push();
    cur_return = dynamic_cast<Type *>(rt);
}

void SymbolTable::push_while(STYPE *rt) {
    push();
    in_while++;
}

void SymbolTable::pop() {
    output::endScope();
    for(auto a:tables_stack.back()){
        a.print();
    }
    tables_stack.pop_back();
    offsets_stack.pop_back();
}

void SymbolTable::pop_while() {
    pop();
    in_while--;
}

void SymbolTable::enter_switch() {
    in_switch=true;
}

void SymbolTable::add_Func(STYPE *f) {
    add_Func(dynamic_cast<Variable *>(f));
}

void SymbolTable::add_Func(Variable *f) {
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

void SymbolTable::add_var(Variable *v, int offset) {
    if(contain_var(v->id->name()) || contain_func(v->id->name()))
        output::errorDef(yylineno, v->id->name());
    Arg new_arg = Arg(dynamic_cast<Variable *>(v), offset);
    tables_stack.back().emplace_back(new_arg);
}

void SymbolTable::add_var(STYPE *v) {
    add_var(dynamic_cast<Variable *>(v),  ++offsets_stack.back());
}

Type *SymbolTable::get_id_type(const Id *id) const {
    for(const auto& i:tables_stack){
        for(auto j : i){
            if(j.var->id->name()==id->name())
                return j.var->type;
        }
    }
    return nullptr;
}

bool SymbolTable::contain_var(const string &name) const {
    auto id = Id(name);
    auto t = get_id_type(&id);
    return t != nullptr;
}

Func *SymbolTable::get_func_type(const Id *id) const {
    for(const auto& i:funcs){
        if(i.var->id->name()==id->name())
            return dynamic_cast<Func *>(i.var->type);
    }
    return nullptr;
}

bool SymbolTable::contain_func(const string &name) const {
    auto id = Id(name);
    auto t = get_func_type(&id);
    return t != nullptr;
}

void SymbolTable::assign(STYPE *id_st, STYPE *exp_st) {
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

void SymbolTable::check_return(STYPE *t) {
    if(!t){
        if(!dynamic_cast<Void *>(cur_return))
            output::errorMismatch(yylineno);
    }
    else if(dynamic_cast<Void *>(t))
        output::errorMismatch(yylineno);
    else{
        Type *ret = (dynamic_cast<Exp *>(t))->type();
        if(ret->name()!=cur_return->name() && !(cur_return->name()=="INT" && ret->name()=="BYTE"))
            output::errorMismatch(yylineno);
    }

}

void SymbolTable::check_while(STYPE *t) const {
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

Type *Id::type() const {
    SymbolTable& st = *SymbolTable::GetInstance();
    if(st.contain_func(name()) || !st.contain_var(name()))
        output::errorUndef(yylineno, name());
    return st.get_id_type(this);

}

Type *Num::type() const {
    return new Int();
}

Type *NumB::type() const {
    return new Byte();
}

NumB::NumB(const string name) : val(stoi(name)){
    if(val>255)
        output::errorByteTooLarge(yylineno, name);
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
    output::printID(var->id->name(), offset,var->type->name());
}
