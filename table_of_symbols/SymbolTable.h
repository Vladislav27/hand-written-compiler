#pragma once

#include "Common.h"

#include "ClassInfo.h"

#include <abstr/StringInterner.h>

#include <memory>
#include <unordered_map>

namespace NSymbolTable {
    class SymbolTable {
        std::unordered_map<const Symbol*, ClassInfo> classes;
        const Symbol* mainClass; // TODO: what should we do with main class?
        Location mainClassLocation;

        std::shared_ptr<StringInterner> interner;

    public:
        SymbolTable() = delete;

        explicit SymbolTable(std::shared_ptr<StringInterner> interner)
            : mainClass(nullptr), interner(std::move(interner)) {
        }

        bool HasClass(const Symbol* id) const;
        const ClassInfo& GetClassInfo(const Symbol* id) const;

        const std::unordered_map<const Symbol*, ClassInfo>& GetClasses() const;

        void InsertClassInfo(const ClassInfo&);
        void SetMainClass(const Symbol*);
        void SetMainClassLocation(const Location&);

        const Symbol* GetMainClassId() const;
        const Location& GetMainClassLocation() const;

        std::shared_ptr<StringInterner> GetInterner() const;

        const VariableInfo* FindIdentifier(const ClassInfo *clazzInfo
                , const NSymbolTable::Symbol *id
                , const MethodInfo *methodInfo = nullptr) const;
        const MethodInfo* FindMethod(const Symbol *methodId
                , const Symbol *classId) const;
    };
}