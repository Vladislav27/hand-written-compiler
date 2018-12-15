#include "X86IRBuilder.h"

#include <irt/activation_records/X86/X86MiniJavaClassStruct.h>
#include <irt/activation_records/X86/X86MiniJavaFrame.h>

#include <irt/translator/IRBuilderVisitor.h>

namespace NIRTree {
    IRForest BuildTree(const NTree::Program &program, const NSymbolTable::SymbolTable &symbolTable) {
        std::unique_ptr<const IFrameBuilder> frameBuilder(new X86MiniJavaFrameBuilder());
        std::unique_ptr<const IClassStructBuilder> classStructBuilder(new X86MiniJavaClassStructBuilder());
        IRBuilderVisitor visitor(classStructBuilder.get(), frameBuilder.get(), symbolTable);

        return visitor.CreateForest(program);
    }
}