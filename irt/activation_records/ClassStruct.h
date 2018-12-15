#pragma once

#include <irt/NodeTypes.h>

#include <table_of_symbols/MethodInfo.h>
#include <table_of_symbols/ClassInfo.h>
#include <table_of_symbols/SymbolTable.h>

#include <vector>

namespace NIRTree {
    interface IClassStruct {
        virtual ~IClassStruct() = default;

        virtual std::string GetTableName() const = 0;

        virtual IExp* GetFieldFrom(const Symbol* fieldName, IExp* base, const Location& location) const = 0;
        virtual IExp* GetVirtualMethodAddress(const Symbol* methodName,
                                              IExp* base, const Location& location) const = 0;
        virtual IExp* AllocateNew(const Location& location) const = 0;
    };

    interface IClassStructBuilder {
        virtual ~IClassStructBuilder() = default;

        virtual IClassStruct* GetClassStruct(const NSymbolTable::ClassInfo& info, const NSymbolTable::SymbolTable&) const = 0;
    };
}