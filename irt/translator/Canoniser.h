#pragma once

#include <irt/IIRMutableVisitor.h>
#include <irt/expressions/IExp.h>
#include <irt/statements/IStm.h>

#include <vector>

namespace NIRTree {

    class CanonisationVisitor;

    class Canoniser {
    public:
        static StmWrapper* RemoveEseqsFromSubtree(ISubtreeWrapper* subtreeWrapper);

        static std::vector<std::unique_ptr<IStm>> Linearise(StmWrapper* wrapper);
        static void Linear(IStm* node, std::vector<std::unique_ptr<IStm>> &stms);

        // main method
        static std::vector<std::unique_ptr<IStm>> Canonise(ISubtreeWrapper* subtreeWrapper);
    };

    class CanonisationVisitor : public IIRMutableVisitor {
        std::unique_ptr<ESeq> highestEseq;

        IStm* reorder(std::unique_ptr<IExp>& exp);
        void reorderEseq();
        IStm* addIfRequired(IStm *stm);

    public:
        CanonisationVisitor() : highestEseq(new ESeq(nullptr, nullptr, {})) {}
        IStm* GetStatement() {
            return highestEseq->stm.release();
        }

        void Visit(Binop *) override;
        void Visit(Call *) override;
        void Visit(Const *) override;
        void Visit(ESeq *) override;
        void Visit(Mem *) override;
        void Visit(Name *) override;
        void Visit(Temp *) override;
        void Visit(Unop *) override;

        void Visit(CJump *) override;
        void Visit(Exp *) override;
        void Visit(Jump *) override;
        void Visit(Move *) override;
        void Visit(LabelStm*) override;

        void Visit(ExprWrapper *) override;
        void Visit(StmWrapper *) override;

        void Visit(ExpList *) override;
        void Visit(Seq *) override;
    };
}