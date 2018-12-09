#pragma once

#include "INode.h"

#include <irt/expressions/IExp.h>
#include <irt/statements/IStm.h>

namespace NIRTree {
    // T should has field location
    template <typename T>
    class List : public T {
    public:
        std::unique_ptr<T> head;
        std::unique_ptr<T> tail;

        List(T *_head, T *_tail, const Location &_location = {})
            : T(_location), head(_head), tail(_tail) {
        }
            
        void Accept(IIRVisitor *visitor) const override;
        void Accept(IIRMutableVisitor *visitor) override;

        virtual bool IsCommutative() const { return false; }
        virtual bool IsAbsolutelyCommutative() const { return false; }
    };

    using ExpList = List<IExp>;
    using StmList = List<IStm>;
}