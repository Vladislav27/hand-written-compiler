#pragma once

#include "TypeInfo.h"
#include "ClassInfo.h"


namespace NSymbolTable {
    class ScopeSwitcher {
    public:
        void SwitchClass(ClassInfo *clazz);
        void SwitchMethod(MethodInfo *method);
        void SwitchExprType(TypeInfo *type);

        const ClassInfo *CurrentClass() const;
        const MethodInfo *CurrentMethod() const;
        const TypeInfo *CurrentExprType() const;
    private:
        std::unique_ptr<TypeInfo> expressionType;
        std::unique_ptr<ClassInfo> currentClass;
        std::unique_ptr<MethodInfo> currentMethod;
    };
}
