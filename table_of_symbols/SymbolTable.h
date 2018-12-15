#pragma once

#include "Common.h"

#include "ClassInfo.h"

#include <abstr/StringInterner.h>

#include <memory>
#include <unordered_map>

namespace NSymbolTable {
    class SymbolTable {
        std::unordered_map<const NTree::Symbol*, ClassInfo> classes;
        const NTree::Symbol* mainClass;
        NTree::Location mainClassLocation;

        std::shared_ptr<NTree::StringInterner> interner;

    public:
        SymbolTable() = delete;

        explicit SymbolTable(std::shared_ptr<NTree::StringInterner> interner)
            : mainClass(nullptr), interner(std::move(interner)) {
        }

        bool HasClass(const NTree::Symbol* id) const;
        const ClassInfo& GetClassInfo(const NTree::Symbol* id) const;

        const std::unordered_map<const NTree::Symbol*, ClassInfo>& GetClasses() const;

        void InsertClassInfo(const ClassInfo&);
        void SetMainClass(const NTree::Symbol*);
        void SetMainClassLocation(const NTree::Location&);

        const NTree::Symbol* GetMainClassId() const;
        const NTree::Location& GetMainClassLocation() const;

        std::shared_ptr<NTree::StringInterner> GetInterner() const;

        const VariableInfo* FindIdentifier(const ClassInfo *classInfo
                , const NTree::Symbol *id
                , const MethodInfo *methodInfo = nullptr) const;
        const MethodInfo* FindMethod(const NTree::Symbol *methodId
                , const NTree::Symbol *classId) const;
    };
}