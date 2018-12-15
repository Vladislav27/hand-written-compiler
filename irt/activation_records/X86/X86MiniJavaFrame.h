#pragma once

#include <irt/activation_records/IFrame.h>

#include <vector>
#include <unordered_map>

namespace NIRTree {
    class X86MiniJavaFrame: public IFrame {
        std::vector<const NTree::Symbol*> formalIds;
        std::unordered_map<const NTree::Symbol*, std::shared_ptr<const IAccess>> idToAccess;
        std::unordered_map<const NTree::Symbol*, NSymbolTable::VariableInfo> idToInfo;
        const NSymbolTable::SymbolTable &symbolTable;

        int addressExitIndex = -1;
        int formalTopPointer = 0;
        int localTopPointer = 0;

        IAccess* createFormal(IAccess::ERecordsType type, int size);
    public:
        X86MiniJavaFrame(const NSymbolTable::ClassInfo &classInfo, const NSymbolTable::MethodInfo &methodInfo,
                         const NSymbolTable::SymbolTable &symbolTable);

        void AddLocal(const NSymbolTable::VariableInfo &variable) override;
        void AddFormal(const NSymbolTable::VariableInfo &variable) override;
        void AddAddressExit() override;
        void AddAddressReturnValue(const NSymbolTable::TypeInfo &) override {};
        int GetFormalsCount() const override;
        std::shared_ptr<const IAccess> GetFormal(int index) const override;
        std::shared_ptr<const IAccess> GetFormalOrLocal(const NTree::Symbol *id) const override;
        int TypeSize(const NSymbolTable::TypeInfo&) const override;

        static const int MaxInReg;
    };

    class X86MiniJavaFrameBuilder: public IFrameBuilder {
        IFrame* GetFrame(const NSymbolTable::ClassInfo &classInfo
                , const NSymbolTable::MethodInfo &methodInfo
                , const NSymbolTable::SymbolTable &symbolTable) const override;
    };
}