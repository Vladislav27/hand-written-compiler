#pragma once

#include "Common.h"

#include "IdentifierInfo.h"
#include "MethodInfo.h"
#include "VariableInfo.h"

#include <util/Symbol.h>

#include <unordered_map>

namespace NSymbolTable {
    class ClassInfo : public IdentifierInfo {
        std::unordered_map<const Symbol *, VariableInfo> membersInfo;
        std::unordered_map<const Symbol *, MethodInfo> methodsInfo;
        const Symbol *superClassId;

    public:
        ClassInfo(const Symbol *_classId, const NSyntaxTree::Location &_location,
                  const Symbol *_superClassId = nullptr);

        void InsertVarInfo(const VariableInfo &varInfo);

        void InsertMethodInfo(const MethodInfo &methodInfo);

        bool HasMember(const Symbol *id) const;
        bool HasMethod(const Symbol *id) const;

        TypeInfo GetType() const;

        const std::unordered_map<const Symbol *, VariableInfo> &GetVarsInfo() const { return membersInfo; }

        const std::unordered_map<const Symbol *, MethodInfo> &GetMethodsInfo() const { return methodsInfo; }

        const Symbol *GetSuperClassId() const { return superClassId; }
    };
}