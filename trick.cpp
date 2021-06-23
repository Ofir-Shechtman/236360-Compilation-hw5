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
    merge(s);
    auto temp = CodeBuffer::merge(b->data.falseList, nextList);
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

Statement::Statement(MarkerM * m1, STYPE * sb, MarkerM * m2, Statement* s) {
    auto b= dynamic_cast<Boolean*>(sb);
    auto& cb = CodeBuffer::instance();
    merge(s);
    cb.bpatch(nextList, m1->label);
    cb.bpatch(continueList, m1->label);
    cb.bpatch( b->data.trueList, m2->label);
    nextList = b->data.falseList;
    CodeBuffer::instance().emit(br_uncond(m1->label));
    cb.bpatch(CodeBuffer::merge(s->breakList, b->data.falseList), cb.genLabel());





}

Statement::Statement(int type) {
    if(type == 1) {//break
        auto& cb = CodeBuffer::instance();
        auto br = cb.emit(br_uncond("@"));
        breakList = CodeBuffer::makelist(pii(br,FIRST));

    }
    else if(type == 2) {//continue
        auto& cb = CodeBuffer::instance();
        auto br = cb.emit(br_uncond("@"));
        continueList = CodeBuffer::makelist(pii(br,FIRST));
    }
}

Statement::Statement(Exp* e, MarkerN* n, CaseList* cl) {
    CodeBuffer::instance().bpatch(n->nextList, CodeBuffer::instance().genLabel());
    string next_label;
    for(int i=0 ;i<cl->cl.size();++i){

        if(!cl->cl[i]->num){//default
            CodeBuffer::instance().emit(br_uncond(cl->cl[i]->m->label));
            next_label = CodeBuffer::instance().genLabel();
            nextList = CodeBuffer::merge(nextList, cl->cl[i]->nextList);
        }

        else{
            auto reg=RegisterManager::instance().alloc(1);
            CodeBuffer::instance().emit(get_binop(reg->name(), "icmp eq", e->get(), cl->cl[i]->num->get(false)));
            auto next_cmd = CodeBuffer::instance().emit(br_cond(reg->full_name(), cl->cl[i]->m->label,"@"));
            next_label = CodeBuffer::instance().genLabel();
            CodeBuffer::instance().bpatch(CodeBuffer::makelist(pii(next_cmd, SECOND)), next_label);
            if(i<cl->cl.size()-1)
                CodeBuffer::instance().bpatch(cl->cl[i]->nextList, cl->cl[i+1]->m->label);
            else
                nextList = CodeBuffer::merge(nextList, cl->cl[i]->nextList);
            nextList = CodeBuffer::merge(nextList, cl->cl[i]->breakList);
        }

    }
    CodeBuffer::instance().bpatch(nextList, next_label);
}

Statement::Statement(MarkerAssign *m, Exp *e) {
    auto b = dynamic_cast<Boolean*>(e);
    if(!b) return;
    auto& cb = CodeBuffer::instance();
    //is true
    auto true_label =  CodeBuffer::instance().genLabel();
    cb.bpatch(b->data.trueList, true_label);
    SymbolTable::GetInstance()->assign(m->id, new Boolean(true, false), false);
    auto after_true = CodeBuffer::instance().emit(br_uncond("@"));
    nextList = CodeBuffer::makelist(pii(after_true, FIRST));

    //is false
    auto false_label =  CodeBuffer::instance().genLabel();
    cb.bpatch(b->data.falseList, false_label);
    SymbolTable::GetInstance()->assign(m->id, new Boolean(false, false), false);
    auto after_false = CodeBuffer::instance().emit(br_uncond("@"));
    nextList =  CodeBuffer::merge(nextList, CodeBuffer::makelist(pii(after_false, FIRST)));

    //after all
    cb.bpatch(nextList, cb.genLabel());


}


Boolean::Boolean(STYPE *e1, STYPE *sop, STYPE *sm, STYPE *e2) {
    is_raw=false;
    auto id1=dynamic_cast<Id*>(e1);
    if(id1)
        e1=SymbolTable::GetInstance()->get_id_arg(id1)->var->exp;
    auto id2=dynamic_cast<Id*>(e2);
    if(id2)
        e2=SymbolTable::GetInstance()->get_id_arg(id2)->var->exp;
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