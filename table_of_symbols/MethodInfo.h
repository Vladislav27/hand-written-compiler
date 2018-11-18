#pragma once

#include "Common.h"

#include "IdentifierInfo.h"
#include "TypeInfo.h"
#include "VariableInfo.h"

#include <abstr/tree/MethodDeclaration.h>
#include <abstr/Symbol.h>

#include <vector>

namespace NSymbolTable {
    class MethodInfo : public IdentifierInfo {
        TypeInfo returnType;
        NTree::EModifier modifier;
        std::vector<VariableInfo> argsInfo;
        std::unordered_map<const NTree::Symbol*, VariableInfo> argsMap;
        std::unordered_map<const NTree::Symbol*, VariableInfo> varsInfo;

    public:
        MethodInfo(const NTree::Symbol* _methodId
                , NTree::Location _location
                , TypeInfo _returnType
                , NTree::EModifier _modifier);

        void InsertArgumentInfo(const VariableInfo& argInfo);
        void InsertVariableInfo(const VariableInfo& varInfo);
            
        const TypeInfo& GetReturnType() const { return returnType; }
        NTree::EModifier GetModifier() const { return modifier; }
        const std::vector<VariableInfo> &GetArgsInfo() const { return argsInfo; }
        const std::unordered_map<const NTree::Symbol*, VariableInfo> &GetVarsInfo() const { return varsInfo; }
        const std::unordered_map<const NTree::Symbol*, VariableInfo> &GetArgsMap() const { return argsMap; }
    };
}