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
        string l=ev1->get(), r=ev2->get();
        reg=RegisterManager::instance().alloc(1);
        CodeBuffer::instance().emit(get_binop(reg->name(), arith, l, r));
        auto nextInstr = CodeBuffer::instance().emit(br_cond(reg->full_name(), "@", "@"));
        data.add(nextInstr, FIRST, nextInstr, SECOND);

    }
    else
        output::errorMismatch(yylineno);
}



Boolean::Boolean(STYPE *e) {
    is_raw=false;
    if(is_bool(e)) {
        auto temp = data.falseList;
        data.falseList = data.trueList;
        data.trueList = temp;

    }
    output::errorMismatch(yylineno);
}

Boolean::Boolean(bool val) :Exp(val), data(){
    //auto nextInstr = CodeBuffer::instance().emit(br_uncond("@"));
    //data.add(nextInstr, FIRST, val);

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

string Exp::get() const {
    if(reg)
        return reg->full_name();
    else
        return type()->reg_type()+ " "+ to_string(val);
}

Exp *binop(STYPE *e1, STYPE *op, STYPE *e2) {
    if(!is_num(e1) ||  !is_num(e2))
        output::errorMismatch(yylineno);
    auto ev1 = dynamic_cast<Exp*>(e1);
    auto ev2 = dynamic_cast<Exp*>(e2);
    if(ev1->type()->name()!=ev2->type()->name())
        output::errorMismatch(yylineno);
    Exp *exp = nullptr;
    if(ev1->type()->name()=="INT")
        exp = new Num("0");
    else if(ev1->type()->name()=="BYTE")
        exp = new NumB("0");
    OP* binop = dynamic_cast<OP*>(op);
    if(!binop)
        output::errorMismatch(yylineno);
    string arith;
    if(binop->op=="/"){
//        if(v2==0) {
//            output::errorDivisionByZero();
//        }
        //exp->val=v1/v2;
        arith = "sdiv";
    }
    else if(binop->op=="*") {
        //exp->val=v1*v2;
        arith = "mul";
    }
    else if(binop->op=="+") {
        //exp->val=v1+v2;
        arith = "add";
    }
    else if(binop->op=="-") {
        //exp->val=v1-v2;
        arith = "sub";
    }
    else {
        output::errorMismatch(yylineno);
    }
    exp->reg=RegisterManager::instance().alloc(32);
    CodeBuffer::instance().emit(get_binop(exp->reg->name(), arith, ev1->get(), ev2->get()));
    if(exp->type()->name()=="BYTE"){
        //<result> = shl i32 4, 2
        exp->reg=RegisterManager::instance().alloc(32);
        CodeBuffer::instance().emit(get_binop(exp->reg->name(), "shl", exp->reg->name(), "24"));
        exp->reg=RegisterManager::instance().alloc(32);
        CodeBuffer::instance().emit(get_binop(exp->reg->name(), "shr", exp->reg->name(), "24"));

    }
    return exp;
}

string Id::get() const {
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
    return arg->var->exp->reg->full_name();
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
            this->exp = new Boolean();
    }

}
