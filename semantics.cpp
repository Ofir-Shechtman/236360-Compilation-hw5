#include "semantics.hpp"
#include "SymbolTable.hpp"
#include "bp.hpp"
#include "llvm_funcs.hpp"


Type *Num::type() const {
    return new Int();
}

Type *NumB::type() const {
    return new Byte();
}


Type *Boolean::type() const {
    return new Bool();
}

Boolean::Boolean(STYPE *e1, STYPE* op, STYPE *e2) {
    is_raw=false;
    auto ev1 = dynamic_cast<Exp*>(e1);
    auto ev2 = dynamic_cast<Exp*>(e2);
    if(is_num(ev1) &&  is_num(ev2)){
        //int v1 = ev1->getVal();
        //int v2 = ev2->getVal();
        OP* my_op = dynamic_cast<OP*>(op);
        if(!my_op)
            output::errorMismatch(yylineno);
        string arith = "icmp ";
        if(my_op->op=="==")
            arith +="eq";
            //val=(v1==v2);
        else if(my_op->op=="!=")
            arith +="ne";
            //val=(v1!=v2);
        else if(my_op->op=="<=")
            arith +="sle";
            //val=(v1<=v2);
        else if(my_op->op==">=")
            arith +="sge";
            //val=(v1>=v2);
        else if(my_op->op=="<")
            arith +="slt";
            //val=(v1<v2);
        else if(my_op->op==">")
            arith +="sgt";
            //val=(v1>v2);
        else
            output::errorMismatch(yylineno);
        string l=ev1->get(), r=ev2->get(false);
        reg=RegisterManager::instance().alloc(1);
        CodeBuffer::instance().emit(get_binop(reg->name(), arith, l, r));
        auto nextInstr = CodeBuffer::instance().emit(br_cond(reg->full_name(), "@", "@"));
        data.add(nextInstr, FIRST, nextInstr, SECOND);

    }
    else
        output::errorMismatch(yylineno);
}



Boolean::Boolean(STYPE *e) {//not
    is_raw=false;
    if(is_bool(e)) {
        auto id=dynamic_cast<Id*>(e);
        if(id)
            e=SymbolTable::GetInstance()->get_id_arg(id)->var->exp;
        auto b = dynamic_cast<Boolean*>(e);
        if(!b)
            b=dynamic_cast<Boolean*>(dynamic_cast<Call*>(e)->e);
        auto temp = b->data.falseList;
        data.falseList = b->data.trueList;
        data.trueList = temp;

    }
    else
        output::errorMismatch(yylineno);
}

Boolean::Boolean(bool val, bool br) :Exp(val), data(){
    if(br) {
        auto nextInstr = CodeBuffer::instance().emit(br_uncond("@"));
        data.add(nextInstr, FIRST, val);
        is_raw=true;
    }

}

Boolean::Boolean(Id* id) {
    //auto nextInstr = CodeBuffer::instance().emit(br_cond(id->name()));
    //data.add(nextInstr, FIRST, true);
    //data.add(nextInstr, SECOND, false);

}


Type *String::type() const {
    return new TypeString();
}

String::String(string val) :str(val.substr(1,val.size()-2)){
    val =val.substr(1,val.size()-2);
    for(auto i:SymbolTable::GetInstance()->const_strings){
        if(i->str==val){
            const_name = i->const_name;
            return;
        }
    }
    SymbolTable::GetInstance()->const_strings.emplace_back(this);
    const_name = "const_"+ to_string(SymbolTable::GetInstance()->const_strings.size());
    CodeBuffer::instance().emitGlobal(internal_const(const_name, str.length(), str));

}

string String::get(bool full_const) const {
    auto newreg = RegisterManager::instance().alloc(32);
    CodeBuffer::instance().emit(getelementptr(newreg->name(), str.size()+2, const_name));
    if(full_const)
        return "i8* " + newreg->name();
    return newreg->name();
}

bool is_type(STYPE* e, string type) {
    Exp* exp=dynamic_cast<Exp*>(e);
    if(!exp)
        return false;
    auto id=dynamic_cast<Id*>(e);
    if(id)
        exp=SymbolTable::GetInstance()->get_id_arg(id)->var->exp;
    string t;
    if(exp)
        t=exp->type()->name();
    else
        t=dynamic_cast<Call*>(e)->type()->name();
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
    vector<string> str_args;
    auto br = CodeBuffer::instance().emit(br_uncond());
    auto call_label = CodeBuffer::instance().genLabel();
    CodeBuffer::instance().bpatch(CodeBuffer::makelist(pii(br,FIRST)), call_label);
    for(auto a:el->exp_list){
        str_args.emplace_back(a->exp->get(true));
        if(a->type->name()=="BOOL") {
            auto b = dynamic_cast<Boolean*>(a->exp);
            auto l = b->data.falseList;
            if(b->val)
                l = b->data.trueList;
            CodeBuffer::instance().bpatch(l, call_label);
        }
    }
    if(st->get_func_type(id)->RetType->name()=="VOID")
        CodeBuffer::instance().emit(call_void(t->reg_type(), id->name(), str_args));
    else {

        if(t->name()=="INT")
            e = new Num("0");
        else if(t->name()=="BYTE")
            e = new NumB("0");
        else if(t->name()=="BOOL")
            e = new Boolean(false, false);

        e->reg = RegisterManager::instance().alloc(t->name()=="BOOL" ? 1 :32);
        CodeBuffer::instance().emit(
                call(e->reg->name(), t->reg_type(), id->name(), str_args));

        auto b = dynamic_cast<Boolean*>(e);
        if(b){
            auto nextInstr = CodeBuffer::instance().emit(br_cond(b->get()));
            b->data.add(nextInstr, FIRST, true);
            b->data.add(nextInstr, SECOND, false);
        }
    }
}

void ExpList::add(ExpType *et) {
    auto exp = et->exp;
    if(!exp)
        output::errorSyn(yylineno);
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
    if(offset<0){
        cout << "%" << offset*-1-1 << endl;
    }
    else {
        int val = var->exp->val;
        cout << "%ptr" << offset << " = " << val << endl;
    }

}

string Arg::ptr_name() const {
    return "%ptr" + to_string(offset);
}

string Exp::get(bool full_const) const {
    if (reg){
        if(full_const)
            return reg->full_name();
        else
            return reg->name();
    }
    else if (full_const)
        return type()->reg_type() + " " + to_string(val);
    else
        return to_string(val);
}


Exp *binop(STYPE *e1, STYPE *op, STYPE *e2) {
    if(!is_num(e1) ||  !is_num(e2))
        output::errorMismatch(yylineno);
    auto ev1 = dynamic_cast<Exp*>(e1);
    auto ev2 = dynamic_cast<Exp*>(e2);
    //if(ev1->type()->name()!=ev2->type()->name())
    //    output::errorMismatch(yylineno);
    Exp *exp = nullptr;
    if(ev1->type()->name()=="INT" || ev2->type()->name()=="INT")
        exp = new Num("0");
    else if(ev1->type()->name()=="BYTE")
        exp = new NumB("0");
    OP* binop = dynamic_cast<OP*>(op);
    if(!binop)
        output::errorMismatch(yylineno);
    string arith;
    auto v1 = ev1->val, v2 = ev2->val;
    if(binop->op=="/"){
//        if(v2==0) {
//            output::errorDivisionByZero();
//        }
        auto& cb = CodeBuffer::instance();
        auto is_zero=RegisterManager::instance().alloc(1);
        cb.emit(get_binop(is_zero->name(), "icmp eq", ev2->get(), "0"));
        auto cmp=cb.emit(br_cond(is_zero->full_name()));
        auto raise_lbl = cb.genLabel();
        cb.emit(call_void("void","errorDivisionByZero"));
        auto after = cb.emit(br_uncond());
        auto next_label = cb.genLabel();
        cb.bpatch(CodeBuffer::makelist(pii(after, FIRST)), next_label);
        cb.bpatch(CodeBuffer::makelist(pii(cmp, SECOND)), next_label);
        cb.bpatch(CodeBuffer::makelist(pii(cmp, FIRST)), raise_lbl);
        //exp->val=v1/v2;
        arith = "sdiv";
    }
    else if(binop->op=="*") {
        exp->val=v1*v2;
        arith = "mul";
    }
    else if(binop->op=="+") {
        exp->val=v1+v2;
        arith = "add";
    }
    else if(binop->op=="-") {
        exp->val=v1-v2;
        arith = "sub";
    }
    else {
        output::errorMismatch(yylineno);
    }
    exp->reg=RegisterManager::instance().alloc(32);
    CodeBuffer::instance().emit(get_binop(exp->reg->name(), arith, ev1->get(), ev2->get(false)));
    if(exp->type()->name()=="BYTE"){
        auto new_reg=RegisterManager::instance().alloc(32);
        CodeBuffer::instance().emit(get_binop(new_reg->name(), "and", exp->reg->full_name(), "255"));
        //%scale2 = trunc i32 %scale to i8
//        CodeBuffer::instance().emit(new_reg->name()+" = trunc i32 " + exp->reg->name()+" to i8");
//        exp->reg=new_reg;
//
//        //%X = zext i32 257 to i64
//        new_reg=RegisterManager::instance().alloc(32);
//        CodeBuffer::instance().emit(new_reg->name()+" = zext i8 " + exp->reg->name()+" to i32");
        exp->reg=new_reg;


    }
    return exp;
}

string Id::get(bool full_const) const {
    auto arg = SymbolTable::GetInstance()->get_id_arg(this);
    if (!arg)
        output::errorUndef(yylineno, this->name());
    if (!arg->var->exp->reg){
        int bit = arg->var->type->name()=="BOOL" ? 1 : 32;
        auto& reg = arg->var->exp->reg;
        reg=RegisterManager::instance().alloc(bit);
        string ptr_name = "%ptr" + to_string(arg->offset);
        CodeBuffer::instance().emit(load(reg->name(), reg->type(), ptr_name));
    }
    if(full_const)
        return arg->var->exp->reg->full_name();
    else
        return arg->var->exp->reg->name();
}
Variable::Variable(STYPE *type, STYPE *id, STYPE *exp) : type(dynamic_cast<Type *>(type)),
                                                         id(dynamic_cast<Id *>(id)),
                                                         exp(dynamic_cast<Exp *>(exp)){
    if(!exp || !this->exp->is_raw){
        if(this->type->name()=="INT")
            this->exp = new Num("0");
        else if(this->type->name()=="BYTE")
            this->exp = new NumB("0");
        else if(this->type->name()=="BOOL")
            this->exp = new Boolean(this->id);
    }

}

ExpType::ExpType(Exp *e) :type(e->type()), exp(e){
    if(exp->type()->name()=="BOOL" && !exp->is_raw) {
        auto b = dynamic_cast<Boolean *>(exp);
        auto& cb = CodeBuffer::instance();
        auto true_label = cb.genLabel();
        auto next_list = CodeBuffer::makelist(pii(cb.emit(br_uncond()), FIRST));
        cb.instance().bpatch(b->data.trueList, true_label);
        auto false_label = cb.genLabel();
        next_list = CodeBuffer::merge(next_list, CodeBuffer::makelist(pii(cb.emit(br_uncond()), FIRST)));
        cb.instance().bpatch(b->data.falseList, false_label);
        pair<string, string> p1("1", "%"+true_label),p2("0", "%"+false_label);
        vector<pair<string, string>> pairs = {p1, p2};
        exp->reg = RegisterManager::instance().alloc(1);
        auto phi_ = cb.genLabel();
        cb.emit((phi(exp->reg->name(), "i1", pairs)));
        cb.bpatch(next_list, phi_);
    }
}
