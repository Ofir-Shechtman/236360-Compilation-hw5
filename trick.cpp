//
// Created by ofir5 on 20/06/21.
//

#include "trick.hpp"
#include "semantics.hpp"

Statement::Statement(IfStatement *ifst) {
    auto b=ifst->b;
    auto m=ifst->s->m;
    auto s=ifst->s->s;
    auto& cb = CodeBuffer::instance();
    auto last_goto = CodeBuffer::instance().emit(br_uncond("@"));
    nextList = CodeBuffer::makelist(pii(last_goto, FIRST));
    cb.bpatch(b->data.trueList, m->label);
    auto temp = CodeBuffer::merge(b->data.falseList, s->nextList);
    nextList= CodeBuffer::merge(nextList, temp);
    cb.bpatch(nextList, cb.genLabel());


}

Statement::Statement(IfStatement *ifst, MarkerN* n, Scope *s) {
    auto b=ifst->b;
    auto m1=ifst->s->m;
    auto s1=ifst->s->s;
    auto m2=s->m;
    auto s2=s->s;
    auto& cb = CodeBuffer::instance();
    auto last_goto = CodeBuffer::instance().emit(br_uncond("@"));
    nextList = CodeBuffer::makelist(pii(last_goto, FIRST));
    cb.bpatch(b->data.trueList, m1->label);
    cb.bpatch(b->data.falseList, m2->label);
    auto temp1 =CodeBuffer::merge(s1->nextList, n->nextList);
    auto temp2 = CodeBuffer::merge(temp1, s2->nextList);
    nextList = CodeBuffer::merge(temp2, nextList);
    cb.bpatch(nextList, cb.genLabel());

}


Boolean::Boolean(STYPE *e1, STYPE *sop, STYPE *sm, STYPE *e2) {
    is_raw=false;
    auto b1 = dynamic_cast<Boolean *>(e1);
    auto op = dynamic_cast<OP *>(sop);
    auto b2 = dynamic_cast<Boolean *>(e2);
    auto m = dynamic_cast<MarkerM *>(sm);

    if (b1 && op && b2 && m) {
        auto &cb = CodeBuffer::instance();
        if (op->op == "or") {
            cb.bpatch(b1->data.falseList, m->label);
            data.trueList = CodeBuffer::merge(b1->data.trueList,
                                              b2->data.trueList);
            data.falseList = b2->data.falseList;
        } else if (op->op == "and") {
            cb.bpatch(b1->data.trueList, m->label);
            data.trueList = b2->data.trueList;
            data.falseList = CodeBuffer::merge(b1->data.falseList,
                                               b2->data.falseList);
        }
    } else
        output::errorMismatch(yylineno);
}