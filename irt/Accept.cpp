#include <irt/expressions/Binop.h>
#include <irt/expressions/Call.h>
#include <irt/expressions/Const.h>
#include <irt/expressions/ESeq.h>
#include <irt/expressions/Mem.h>
#include <irt/expressions/Name.h>
#include <irt/expressions/Temp.h>

#include <irt/statements/CJump.h>
#include <irt/statements/Exp.h>
#include <irt/statements/Jump.h>
#include <irt/statements/Label.h>
#include <irt/statements/Move.h>
#include <irt/statements/Seq.h>

#include <irt/translator/ExprWrapper.h>
#include <irt/translator/StmWrapper.h>

#include <irt/IIRVisitor.h>
#include <irt/IIRMutableVisitor.h>

namespace NIRTree {
    void Binop::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Call::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Const::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void ESeq::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Mem::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Name::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Temp::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Unop::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void CJump::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Exp::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Jump::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void LabelStm::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void Move::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    template<>
    void List<IStm>::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    template<>
    void List<IExp>::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void ExprWrapper::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    void StmWrapper::Accept(IIRVisitor *visitor) const {
        visitor->Visit(this);
    }

    // IIRMutableVisitor
    void Binop::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void Call::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void Const::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void ESeq::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void Mem::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void Name::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void Temp::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void Unop::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void CJump::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void Exp::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void Jump::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void LabelStm::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void Move::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    template<>
    void List<IStm>::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    template<>
    void List<IExp>::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void ExprWrapper::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }

    void StmWrapper::Accept(IIRMutableVisitor *visitor) {
        visitor->Visit(this);
    }


}
