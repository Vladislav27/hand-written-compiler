#pragma once

#include "Common.h"

#include "INode.h"
#include "Class.h"


namespace NTree {
    struct Program : public INode {
        unique_ptr<MainClass> mainClass;

        void Accept(IVisitor *visitor) const override;
    };
}