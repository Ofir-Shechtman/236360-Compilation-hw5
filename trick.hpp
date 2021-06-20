#ifndef HW5_TRICK_H
#define HW5_TRICK_H

#include "semantics.hpp"
#include "llvm_funcs.hpp"
#include "bp.hpp"
#include <vector>
#include <string>

#endif //HW5_TRICK_H

class IfStatement;
class Scope;
class MarkerN;

struct Statement: public STYPE{
    vector<pair<int,BranchLabelIndex>> nextList;
    Statement()=default;
    explicit Statement(IfStatement *ifst);
    Statement(IfStatement *ifst, MarkerN* n, Scope* m);
    void merge(Statement * s){
        nextList=CodeBuffer::merge(nextList, s->nextList);
    }
//    explicit Statement(int next_label, BranchLabelIndex idx){
//        pair<int,BranchLabelIndex> item(next_label, idx);
//        nextList = CodeBuffer::makelist(item);
//    }
};



struct MarkerM: public STYPE{
    int instr;
    MarkerM():instr(CodeBuffer::instance().nextInst()) {
        CodeBuffer::instance().genLabel();

    }
};

struct MarkerN: public STYPE{
    vector<pair<int,BranchLabelIndex>> nextList;
    MarkerN():nextList(CodeBuffer::makelist(pair<int,BranchLabelIndex>(CodeBuffer::instance().nextInst(), FIRST))) {
        CodeBuffer::instance().emit(br_uncond("@"));
        //CodeBuffer::instance().genLabel();
    }

};


struct Scope: public STYPE{
    Statement* s;
    MarkerM* m;
    Scope(STYPE* m, STYPE* s):s(dynamic_cast<Statement*>(s)), m(dynamic_cast<MarkerM*>(m)){}
};

struct IfStatement: public STYPE{
    Boolean* b;
    Scope* s;
    IfStatement(STYPE* e, STYPE* s):b(dynamic_cast<Boolean*>(e)), s(dynamic_cast<Scope*>(s)){}
};
