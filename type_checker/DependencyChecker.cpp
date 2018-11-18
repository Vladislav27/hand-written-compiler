#include "DependencyChecker.h"

namespace NTypeChecker {
    void CheckDependencies(const NSymbolTable::SymbolTable& symbolTable) {
        /*
         * Тут должны проверяться две вещи:
         * отсутствие циклических зависимостей и существование в глобальной области видимости классов,
         * упомянутых в extends.
         * Нарушение первого должно бросать CyclicDependencyException, второго - NonDeclaredSymbolException
         */

        for (auto it = symbolTable.GetClasses().begin(); it != symbolTable.GetClasses().end(); ++it) {
            NSymbolTable::ClassInfo currentClassInfo = it->second;

            const NUtil::Symbol *superClassId = currentClassInfo.GetSuperClassId();
            if (superClassId != nullptr) {
                if (!symbolTable.HasClass(superClassId)) {
                    throw NSymbolTable::NonDeclaredSymbolException(
                        symbolTable.GetClassInfo(superClassId).GetLocation(),
                        superClassId
                    );
                }
                CheckInClass(symbolTable, currentClassInfo.GetSuperClassId(), currentClassInfo);
            }
        }
    }

    void CheckInClass(const NSymbolTable::SymbolTable& symbolTable,
        const NUtil::Symbol* superClassId,
        const NSymbolTable::ClassInfo& childClassInfo) {

        // получим classInfo для superClassId
        NSymbolTable::ClassInfo superClassInfo = symbolTable.GetClassInfo(superClassId);

        // Теперь нужно проверить, не совпадает ли имя superClass с именем childClass
        const std::string superClassName = superClassInfo.GetId()->String();
        const std::string childClassName = childClassInfo.GetId()->String();

        if (superClassName == childClassName) {
            throw NSymbolTable::CyclicDependencyException(childClassInfo.GetLocation(),
                                                          childClassInfo.GetId());
            return;
        }

        // Дальше нужно запустить обход глубже - в superClass для superClass
        const NUtil::Symbol *superSuperClassId = superClassInfo.GetSuperClassId();
        if (superSuperClassId != nullptr) {
            CheckInClass(symbolTable, superSuperClassId, childClassInfo);
        }
    }
}