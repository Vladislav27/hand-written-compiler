#include "SymbolTable.h"

namespace NSymbolTable {
    bool SymbolTable::HasClass(const NUtil::Symbol* id) const {
        return classes.find(id) != classes.end();
    }

    const ClassInfo &SymbolTable::GetClassInfo(const Symbol* id) const {
        return classes.at(id);
    }

    void SymbolTable::InsertClassInfo(const ClassInfo& classInfo) {
        classes.insert({classInfo.GetId(), classInfo});
    }

    const std::unordered_map<const Symbol *, ClassInfo>& SymbolTable::GetClasses() const {
        return classes;
    }

    void SymbolTable::SetMainClass(const Symbol* id) {
        mainClass = id;
    }

    const Symbol *SymbolTable::GetMainClassId() const {
        return mainClass;
    }

    std::shared_ptr<StringInterner> SymbolTable::GetInterner() const {
        return interner;
    }

    void SymbolTable::SetMainClassLocation(const Location &location) {
        mainClassLocation = location;
    }

    const Location &SymbolTable::GetMainClassLocation() const {
        return mainClassLocation;
    }

    const VariableInfo *SymbolTable::FindIdentifier(const ClassInfo *clazzInfo,
                                                    const NSymbolTable::Symbol *id,
                                                    const MethodInfo *methodInfo) const {
        if (methodInfo) {
            if (methodInfo->GetArgsMap().find(id) != methodInfo->GetArgsMap().end()) {
                return &methodInfo->GetArgsMap().at(id);
            }

            if (methodInfo->GetVarsInfo().find(id) != methodInfo->GetVarsInfo().end()) {
                return &methodInfo->GetVarsInfo().at(id);
            }
        }

        auto clazz = *clazzInfo;
        while (!clazz.HasMember(id) && clazz.GetSuperClassId() != nullptr) {
            clazz = GetClassInfo(clazz.GetSuperClassId());
        }

        if (!clazz.HasMember(id)) {
            return nullptr;
        }

        return &clazz.GetVarsInfo().at(id);
    }

    const MethodInfo *SymbolTable::FindMethod(const NUtil::Symbol *methodId, const NUtil::Symbol *classId) const {
        auto classInfo = GetClassInfo(classId);

        while (!classInfo.HasMethod(methodId) && classInfo.GetSuperClassId() != nullptr) {
            classInfo = GetClassInfo(classInfo.GetSuperClassId());
        }

        if (!classInfo.HasMethod(methodId)) {
            return nullptr;
        }

        return &classInfo.GetMethodsInfo().at(methodId);
    }
}
