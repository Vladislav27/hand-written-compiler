#include "Canoniser.h"
#include "IRPrettyPrinter.h"

#include <cassert>
#include <vector>


namespace NIRTree {

    StmWrapper *Canoniser::RemoveEseqsFromSubtree(ISubtreeWrapper *subtreeWrapper) {
        CanonisationVisitor cv;
        subtreeWrapper->Accept(&cv);
        return new StmWrapper(cv.GetStatement());
    }

    std::vector<std::unique_ptr<IStm>> Canoniser::Linearise(StmWrapper *wrapper) {
        std::vector<std::unique_ptr<IStm>> stms;
        Linear(wrapper->ToStm(), stms);
        return stms;
    }

    void Canoniser::Linear(IStm *node, std::vector<std::unique_ptr<IStm>> &stms) {
        if (auto list = dynamic_cast<StmList *>(node)) {
            if (list->head) {
                Linear(list->head.release(), stms);
            }
            if (list->tail) {
                Linear(list->tail.release(), stms);
            }
        } else {
            stms.emplace_back(node);
        }
    }

    std::vector<std::unique_ptr<IStm>> Canoniser::Canonise(ISubtreeWrapper *subtreeWrapper) {
        return Linearise(RemoveEseqsFromSubtree(subtreeWrapper));
    }

    /*Visitor*/

    void CanonisationVisitor::Visit(Binop *node) {
        IStm *leftStatements = reorder(node->leftExp);
        IStm *rightStatements = reorder(node->rightExp);
        highestEseq->stm.reset(new Seq(leftStatements, rightStatements));
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(Call *node) {
        node->args->Accept(this);
        node->args.release();
        node->args.reset(static_cast<ExpList *>(highestEseq->exp.release()));
        highestEseq->stm.reset(reorder(node->funcExp));
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(Const *node) {
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(ESeq *node) {
        node->stm->Accept(this);
        node->stm.release();
        highestEseq->stm.reset(reorder(node->exp));
        highestEseq->exp.reset(node->exp.release());
        delete node;
    }

    void CanonisationVisitor::Visit(Mem *node) {
        node->exp->Accept(this);
        node->exp.release();
        node->exp.reset(highestEseq->exp.release());
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(Name *node) {
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(Temp *node) {
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(Unop *node) {
        highestEseq->stm.reset(reorder(node->exp));
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(CJump *node) {
        IStm *leftStatements = reorder(node->leftExpr);
        IStm *rightStatements = reorder(node->rightExpr);
        if (leftStatements != nullptr) {
            highestEseq->stm.reset(addIfRequired(leftStatements));
        }
        if (rightStatements != nullptr) {
            highestEseq->stm.reset(addIfRequired(rightStatements));
        }
        highestEseq->stm.reset(addIfRequired(node));
    }

    void CanonisationVisitor::Visit(Exp *node) {
        IStm *stm = reorder(node->exp);
        if (stm != nullptr) {
            highestEseq->stm.reset(addIfRequired(stm));
        }
        highestEseq->stm.reset(addIfRequired(node));
    }

    void CanonisationVisitor::Visit(Jump *node) {
        highestEseq->AppendStm(std::unique_ptr<Jump>(node));
    }

    void CanonisationVisitor::Visit(Move *node) {
        IStm *src = reorder(node->src);
        IStm *dst = reorder(node->dst);
        if (src != nullptr) {
            highestEseq->stm.reset(addIfRequired(src));
        }
        if (dst != nullptr) {
            highestEseq->stm.reset(addIfRequired(dst));
        }
        highestEseq->stm.reset(addIfRequired(node));
    }

    void CanonisationVisitor::Visit(LabelStm *node) {
        highestEseq->AppendStm(std::unique_ptr<LabelStm>(node));
    }

    void CanonisationVisitor::Visit(ExprWrapper *node) {
        node->ToStm()->Accept(this);
    }

    void CanonisationVisitor::Visit(StmWrapper *node) {
        node->ToStm()->Accept(this);
    }

    void CanonisationVisitor::Visit(ExpList *node) {
        if (node->head != nullptr) {
            IStm *stm = reorder(node->head);
            if (stm != nullptr) {
                highestEseq->stm.reset(addIfRequired(stm));
            }
        }
        if (node->tail != nullptr) {
            node->tail->Accept(this);
            node->tail.release();
            node->tail.reset(highestEseq->exp.release());
        }
        highestEseq->exp.reset(node);
    }

    void CanonisationVisitor::Visit(Seq *node) {
        node->head->Accept(this);
        node->head.release();
        if (node->tail != nullptr) {
            node->tail->Accept(this);
        }
        node->tail.release();
        delete node;
    }

    IStm *CanonisationVisitor::reorder(std::unique_ptr<IExp> &exp) {
        exp->Accept(this);
        exp.release();
        reorderEseq();
        exp.reset(highestEseq->exp.release());
        return highestEseq->stm.release();
    }

    void CanonisationVisitor::reorderEseq() {
        if (highestEseq->stm.get() == nullptr || highestEseq->exp.get() == nullptr) {
            return;
        }
        if (highestEseq->exp->IsCommutative()) {
            return;
        } else {
            Temp *holder = new Temp(Temp::TempHolderLocalId);
            highestEseq->stm.reset(new Seq(highestEseq->stm.release(),
                                           new Move(holder, highestEseq->exp.release(), {})));
            highestEseq->exp.reset(new Mem(new Temp(*holder), {}));
        }
    }

    IStm *CanonisationVisitor::addIfRequired(IStm *stm) {
        assert(stm != nullptr);
        if (highestEseq->stm == nullptr) {
            return stm;
        }
        return new Seq(highestEseq->stm.release(), stm);
    }
}