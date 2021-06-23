#include "SymbolTable.hpp"
#include "RegisterManager.hpp"
#include "bp.hpp"
#include "llvm_funcs.hpp"
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

    funcs={new Arg(v1, 0), new Arg(v2, 0)};
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
        if(f->var->id->name()=="main" && f->var->type->name()=="()->VOID") {
            MainMissing= false;
        }
    }
    if(MainMissing) output::errorMainMissing();
    output::endScope();
    for(auto f:funcs){
        //f->print();
    }

}

void SymbolTable::push() {
    tables_stack.emplace_back(vector<Arg*>());
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
        //a->print();
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
    funcs.emplace_back(new Arg(f, 0));
    int offset=-1;
    vector<string> args_type;
    for(auto a:args){
        int bit = a->type->name()=="BOOL" ? 1 : 32;
        a->exp->reg=RegisterManager::instance().alloc(bit, true);
        add_var(a, offset--);
        args_type.emplace_back(a->type->reg_type());
    }
    CodeBuffer::instance().emit(define(f->id->name(), args_type, dynamic_cast<Func *>(f->type)->RetType->reg_type()));
//    for(auto a:args){
//        auto b = dynamic_cast<Boolean*>(a->exp);
//        if(b){
//            auto nextInstr = CodeBuffer::instance().emit(br_cond(b->get()));
//            b->data.add(nextInstr, FIRST, true);
//            b->data.add(nextInstr, SECOND, false);
// //////////////////////////////////////////////////////
//            auto& cb = CodeBuffer::instance();
//            auto nextInstr = cb.emit(br_cond(b->get()));
//
//            auto true_label = cb.genLabel();
//            cb.bpatch(CodeBuffer::makelist(pii(nextInstr, FIRST)), true_label);
//            auto next_list = CodeBuffer::makelist(pii(cb.emit(br_uncond()), FIRST));
//
//            auto false_label = cb.genLabel();
//            cb.bpatch(CodeBuffer::makelist(pii(nextInstr, SECOND)), false_label);
//            next_list = CodeBuffer::merge(next_list, CodeBuffer::makelist(pii(cb.emit(br_uncond()), FIRST)));
//
//            pair<string, string> p1("i1 1", true_label),p2("i1 0", false_label);
//            vector<pair<string, string>> pairs = {p1, p2};
//            b->reg = RegisterManager::instance().alloc(1);
//            auto phi_ = cb.genLabel();
//            cb.emit((phi(b->reg->name(), "i1", pairs)));
//            cb.bpatch(next_list, phi_);
//        }
//    }

}

void SymbolTable::add_var(Variable *v, int offset) {
    if(contain_var(v->id->name()) || contain_func(v->id->name()))
        output::errorDef(yylineno, v->id->name());
    Arg* new_arg = new Arg(dynamic_cast<Variable *>(v), offset);
    tables_stack.back().emplace_back(new_arg);
    if(new_arg->offset>=0) {
        auto& exp = new_arg->var->exp;
        CodeBuffer::instance().emit(get_alloca(new_arg->ptr_name(), new_arg->var->type->reg_type() ,new_arg->var->id->name()));
        CodeBuffer::instance().emit(store(new_arg->var->type->reg_type()+" 0",new_arg->var->type->reg_type() ,new_arg->ptr_name()));

    }

}

void SymbolTable::add_var(STYPE *v) {
    add_var(dynamic_cast<Variable *>(v),  ++offsets_stack.back());
}

Type *SymbolTable::get_id_type(const Id *id) const {
    auto arg = get_id_arg(id);
    if(arg)
        return arg->var->type;
    return nullptr;
}

bool SymbolTable::contain_var(const string &name) const {
    auto id = Id(name);
    auto t = get_id_type(&id);
    return t != nullptr;
}

Func *SymbolTable::get_func_type(const Id *id) const {
    for(const auto& i:funcs){
        if(i->var->id->name()==id->name())
            return dynamic_cast<Func *>(i->var->type);
    }
    return nullptr;
}

bool SymbolTable::contain_func(const string &name) const {
    auto id = Id(name);
    auto t = get_func_type(&id);

    return t != nullptr;
}

void SymbolTable::assign(STYPE *id_st, STYPE *exp_st, bool skip_bool) {
    Id* id = dynamic_cast<Id *>(id_st);
    Type* exp_type = dynamic_cast<Exp *>(exp_st)->type();
    if(!contain_var(id->name()))
        output::errorUndef(yylineno, id->name());
    auto id_t = get_id_type(id);
    if(!(id_t->name() == exp_type->name() || (id_t->name() == "INT" && exp_type->name() == "BYTE")))
        output::errorMismatch(yylineno);
    auto arg = get_id_arg(id);
    arg->var->exp->val=dynamic_cast<Exp *>(exp_st)->val;
    if(!dynamic_cast<Exp *>(exp_st)->is_raw){
        return;
        //output::errorSyn(yylineno);
    }
    if(!skip_bool || arg->var->type->name()!="BOOL") {
        CodeBuffer::instance().emit(store(dynamic_cast<Exp *>(exp_st)->get(),
                                          arg->var->type->reg_type(),
                                          arg->ptr_name()));
        arg->var->exp->reg = nullptr;
    }


}

void SymbolTable::check_return(STYPE *t) {
    if(!t){
        if(!dynamic_cast<Void *>(cur_return))
            output::errorMismatch(yylineno);
    }
    else if(dynamic_cast<Void *>(t)){
        if (!dynamic_cast<Void *>(cur_return))
            output::errorMismatch(yylineno);
        CodeBuffer::instance().emit(ret_void());
    }
    else{
        Type *ret_type = (dynamic_cast<Exp *>(t))->type();
        if(ret_type->name()!=cur_return->name() && !(cur_return->name()=="INT" && ret_type->name()=="BYTE"))
            output::errorMismatch(yylineno);
        auto e = dynamic_cast<Exp *>(t);
        auto b = dynamic_cast<Boolean*>(e);
        if(b){
            auto& cb = CodeBuffer::instance();
            auto true_label = cb.genLabel();
            cb.emit(ret("i1 1"));
            //auto next_list = CodeBuffer::makelist(pii(cb.emit(br_uncond()), FIRST));

            auto false_label = cb.genLabel();
            cb.emit(ret("i1 0"));
            //next_list = CodeBuffer::merge(next_list, CodeBuffer::makelist(pii(cb.emit(br_uncond()), FIRST)));

            //cb.bpatch(next_list, cb.genLabel());
            cb.bpatch(b->data.trueList, true_label);
            cb.bpatch(b->data.falseList, false_label);

        }
        else
            CodeBuffer::instance().emit(ret( e->get()));
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

Arg* SymbolTable::get_id_arg(const Id *id) const {
    for(const auto& i:tables_stack){
        for(auto j : i){
            if(j->var->id->name()==id->name())
                return j;
        }
    }
    return nullptr;
}


void SymbolTable::pop_func() {
    auto t=dynamic_cast<Func*>(funcs.back()->var->type)->RetType->reg_type();
    if(t=="void")
        CodeBuffer::instance().emit(ret_void());
    else
        CodeBuffer::instance().emit(ret(t+" 0"));
    pop();
    CodeBuffer::instance().emit("}\n");
    RegisterManager::instance().reset();
}

Type *Id::type() const {
    SymbolTable& st = *SymbolTable::GetInstance();
    if(st.contain_func(name()) || !st.contain_var(name()))
        output::errorUndef(yylineno, name());
    return st.get_id_type(this);

}

Id::Id(const string val) : id_name(val){}


void Id::run_bool_check(){
    auto arg = SymbolTable::GetInstance()->get_id_arg(this);
    if(!arg) return;
    auto b = dynamic_cast<Boolean*>(arg->var->exp);
    if(b){
        auto nextInstr = CodeBuffer::instance().emit(br_cond(arg->var->id->get()));
        b->data.add(nextInstr, FIRST, true);
        b->data.add(nextInstr, SECOND, false);
    }
}
