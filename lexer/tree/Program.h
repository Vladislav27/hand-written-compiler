#pragma once

#include "Common.h"

#include "INode.h"
#include "Class.h"


namespace NTree {
    class Program : public INode {
    public:
        unique_ptr<MainClass> mainClass;

        void Accept(IVisitor *visitor) const override;
    };
}