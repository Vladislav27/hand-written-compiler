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
        NSyntaxTree::EModifier modifier;
        std::vector<VariableInfo> argsInfo;
        std::unordered_map<const Symbol*, VariableInfo> argsMap;
        std::unordered_map<const Symbol*, VariableInfo> varsInfo;

    public:
        MethodInfo(const Symbol* _methodId
                , Location _location
                , TypeInfo _returnType
                , NSyntaxTree::EModifier _modifier);

        void InsertArgumentInfo(const VariableInfo& argInfo);
        void InsertVariableInfo(const VariableInfo& varInfo);
            
        const TypeInfo& GetReturnType() const { return returnType; }
        NSyntaxTree::EModifier GetModifier() const { return modifier; }
        const std::vector<VariableInfo> &GetArgsInfo() const { return argsInfo; }
        const std::unordered_map<const Symbol*, VariableInfo> &GetVarsInfo() const { return varsInfo; }
        const std::unordered_map<const Symbol*, VariableInfo> &GetArgsMap() const { return argsMap; }
    };
}