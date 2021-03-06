#ifndef HW5_TRICK_H
#define HW5_TRICK_H

#include "semantics.hpp"
#include "llvm_funcs.hpp"
#include "SymbolTable.hpp"
#include "bp.hpp"
#include <vector>
#include <string>
#include "SymbolTable.hpp"

#endif //HW5_TRICK_H

class IfStatement;
class Scope;
class MarkerN;
class MarkerM;
class CaseList;
class MarkerAssign;

struct Statement: public STYPE{
    vector<pair<int,BranchLabelIndex>> nextList;
    vector<pair<int,BranchLabelIndex>> breakList;
    vector<pair<int,BranchLabelIndex>> continueList;
    Statement(int type=0);
    explicit Statement(IfStatement *ifst);
    Statement(IfStatement *ifst, MarkerN* n, Scope* m);
    Statement(MarkerM* m1, STYPE* b, MarkerM* m2, Statement* s); //while
    Statement(Exp* e, MarkerN* n, CaseList* cl); // switch
    Statement(MarkerAssign* m, Exp* e); // assign
    void merge(Statement * s){
        //nextList=CodeBuffer::merge(nextList, s->nextList);
        breakList=CodeBuffer::merge(breakList, s->breakList);
        continueList=CodeBuffer::merge(continueList, s->continueList);
    }
//    explicit Statement(int next_label, BranchLabelIndex idx){
//        pair<int,BranchLabelIndex> item(next_label, idx);
//        nextList = CodeBuffer::makelist(item);
//    }
};



struct MarkerM: public STYPE{
    string label;
    explicit MarkerM(bool uncond_br=false) {
          auto& cb = CodeBuffer::instance();
          int br;
          if(uncond_br) br = cb.emit(br_uncond("@"));
          label = cb.genLabel();
          if(uncond_br) cb.bpatch(CodeBuffer::makelist(pii(br,FIRST)), label);
    }
};

struct MarkerN: public STYPE{
    vector<pair<int,BranchLabelIndex>> nextList;
    MarkerN():nextList(CodeBuffer::makelist(pair<int,BranchLabelIndex>(CodeBuffer::instance().nextInst(), FIRST))) {
        CodeBuffer::instance().emit(br_uncond("@"));
        //CodeBuffer::instance().genLabel();
    }

};


struct Scope: public Statement{
    Statement* s;
    MarkerM* m;
    Scope(STYPE* m, STYPE* s):s(dynamic_cast<Statement*>(s)), m(dynamic_cast<MarkerM*>(m)) {
        merge(this->s);
    }
};

struct IfStatement: public Statement{
    Boolean* b;
    Scope* s;
    IfStatement(STYPE* e, STYPE* s):b(dynamic_cast<Boolean*>(e)), s(dynamic_cast<Scope*>(s)){
        merge(this->s->s);
        if(!b) {
            auto id = dynamic_cast<Id*>(e);
            if(id){
                auto arg = SymbolTable::GetInstance()->get_id_arg(id);
                if (!arg) output::errorUndef(yylineno, id->name());
                b = dynamic_cast<Boolean *>(arg->var->exp);
            }
            else
                b=dynamic_cast<Boolean *>(dynamic_cast<Call *>(e)->e);
        }
    }
};


struct CaseDecl : public Statement{
    MarkerM* m;
    Statement* s;
    Num* num;
    CaseDecl(MarkerM* m, Statement* s, Num* num=nullptr):m(m), s(s), num(num){
        auto br = CodeBuffer::instance().emit(br_uncond("@"));
        nextList = CodeBuffer::makelist(pii(br, FIRST));
        merge(s);
    }
};

struct CaseList : public Statement{
    vector<CaseDecl*> cl;
    explicit CaseList(CaseDecl* c){
        cl.insert(cl.begin(), c);
        merge(c);
    };
    CaseList(CaseDecl* c, CaseList* cl1):cl(cl1->cl) {
        cl.insert(cl.begin(), c);
        merge(c);
        merge(cl1);
    }
};

struct MarkerAssign : public Statement{
    bool is_b;
    string label;
    Id* id;
    explicit MarkerAssign(Id* id):id(id){
        if(id) {
            auto arg = SymbolTable::GetInstance()->get_id_arg(id);
            if(arg)
                is_b = dynamic_cast<Boolean *>(arg->var->exp) != nullptr;
        }
        if(is_b){
            auto& cb = CodeBuffer::instance();
            int br = cb.emit(br_uncond("@"));
            label = cb.genLabel();
            cb.bpatch(CodeBuffer::makelist(pii(br,FIRST)), label);
        }
    }
    explicit MarkerAssign(Type* t, Id* id):id(id){
        if(t) {
            is_b = t->name()=="BOOL";
        }
        if(is_b){
            auto& cb = CodeBuffer::instance();
            int br = cb.emit(br_uncond("@"));
            label = cb.genLabel();
            cb.bpatch(CodeBuffer::makelist(pii(br,FIRST)), label);
        }
    }
};