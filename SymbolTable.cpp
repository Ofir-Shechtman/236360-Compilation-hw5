#include "SymbolTable.hpp"
#include "RegisterManager.hpp"
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