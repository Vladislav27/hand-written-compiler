#pragma once

#include "irt/activation_records/ClassStruct.h"

#include <irt/NodeTypes.h>

#include <table_of_symbols/MethodInfo.h>
#include <table_of_symbols/ClassInfo.h>
#include <table_of_symbols/SymbolTable.h>

#include <vector>
#include <unordered_map>

namespace NIRTree {
    class X86MiniJavaClassStruct : public IClassStruct {
    public:
        explicit X86MiniJavaClassStruct(const NSymbolTable::ClassInfo&, const NSymbolTable::SymbolTable& symbolTable);
        std::string GetTableName() const override;

        IExp* GetFieldFrom(const Symbol* fieldName, IExp* base, const Location& location) const override;
        IExp* GetVirtualMethodAddress(const Symbol* methodName,
                                              IExp* base, const Location& location) const override;
        IExp* AllocateNew(const Location& location) const override;

    private:
        // Vtable
        std::vector<const NSymbolTable::MethodInfo*> vtableEntries;
        // Method name -> vtableEntries[id]
        std::unordered_map<const Symbol*, int> vTableIndices;
        // Field name -> fields[id]
        std::unordered_map<const Symbol*, int> fieldsOffsets;
        const Symbol* className;
    };

    class X86MiniJavaClassStructBuilder : public IClassStructBuilder {
    public:
        IClassStruct* GetClassStruct(const NSymbolTable::ClassInfo& info,
                                     const NSymbolTable::SymbolTable& symbolTable) const override;
    };
}