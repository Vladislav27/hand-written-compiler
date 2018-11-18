#pragma once

#include "Common.h"

#include "INode.h"
#include "Class.h"


namespace NTree {
    class Program : public INode {
    public:
        unique_ptr<MainClass> mainClass;
        unique_ptr<vector<std::unique_ptr<ClassDeclaration>>> classes;
        void Accept(IVisitor *visitor) const override;
    };
}