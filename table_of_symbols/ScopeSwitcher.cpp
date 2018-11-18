#include "ScopeSwitcher.h"


namespace NSymbolTable {

    void ScopeSwitcher::SwitchClass(ClassInfo *clazz) {
        currentClass.reset(clazz);
    }

    void ScopeSwitcher::SwitchMethod(MethodInfo *method) {
        currentMethod.reset(method);
    }

    void ScopeSwitcher::SwitchExprType(TypeInfo *type) {
        expressionType.reset(type);
    }

    const ClassInfo *ScopeSwitcher::CurrentClass() const {
        return currentClass.get();
    }

    const MethodInfo *ScopeSwitcher::CurrentMethod() const {
        return currentMethod.get();
    }

    const TypeInfo *ScopeSwitcher::CurrentExprType() const {
        return expressionType.get();
    }
}