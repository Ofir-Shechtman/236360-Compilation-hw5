//
// Created by ofir5 on 20/06/21.
//

#include "trick.hpp"

Statement::Statement(IfStatement *ifst) {
    auto b=ifst->b;
    auto m=ifst->s->m;
    auto s=ifst->s->s;
    auto& cb = CodeBuffer::instance();
    auto last_goto = CodeBuffer::instance().emit(br_uncond("@"));
    nextList = CodeBuffer::makelist(pii(last_goto, FIRST));
    cb.bpatch(b->data.trueList, cb.buffer[m->instr]);
    auto temp = CodeBuffer::merge(b->data.falseList, s->nextList);
    nextList= CodeBuffer::merge(nextList, temp);
    int else_label = cb.nextInst();
    cb.genLabel();
    cb.bpatch(nextList, cb.buffer[else_label]);


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
    cb.bpatch(b->data.trueList, cb.buffer[m1->instr]);
    cb.bpatch(b->data.falseList, cb.buffer[m2->instr]);
    auto temp1 =CodeBuffer::merge(s1->nextList, n->nextList);
    auto temp2 = CodeBuffer::merge(temp1, s2->nextList);
    nextList = CodeBuffer::merge(temp2, nextList);
    int next_label = cb.nextInst();
    cb.genLabel();
    cb.bpatch(nextList, cb.buffer[next_label]);

}
