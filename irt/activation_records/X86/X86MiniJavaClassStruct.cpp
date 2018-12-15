#include "X86MiniJavaClassStruct.h"

#include <vector>

namespace NIRTree {
    std::string X86MiniJavaClassStruct::GetTableName() const {
        return std::string("_vTable::") + className->String();
    }

    IExp* X86MiniJavaClassStruct::GetFieldFrom(const Symbol *fieldName, IExp *base, const Location &location) const {
        assert(fieldsOffsets.find(fieldName) != fieldsOffsets.end());
        // TODO: use typeSpec
        int wordSize = 4;
        return new Mem(new Binop(Binop::PLUS, base,
                                         new Const(wordSize * (1) + fieldsOffsets.at(fieldName), location),
                                         location), location);
    }

    IExp *X86MiniJavaClassStruct::GetVirtualMethodAddress(const Symbol *methodName, IExp *base,
                                                          const Location &location) const {
        assert(vTableIndices.find(methodName) != vTableIndices.end());
        // TODO: use typeSpec
        int wordSize = 4;
        return new Mem(new Binop(Binop::PLUS, new Mem(base, location),
                                         new Const(wordSize * (1 + vTableIndices.at(methodName)), location),
                                         location), location);
    }

    IExp *X86MiniJavaClassStruct::AllocateNew(const Location &location) const {
        // TODO: use typeSpec
        int wordSize = 4;
        const std::string mallocName = "malloc";

        auto allocArg = new ExpList(new Const(fieldsOffsets.size() +
                wordSize * (vtableEntries.size() + 1), location), nullptr, location);
        const int baseAddressId = 0;
        auto baseAddress = new Temp(baseAddressId, location);
        auto prepareActions = new StmList(new Move(baseAddress,
                new Call(new Name(mallocName, location), allocArg, location), location), nullptr, location);

        prepareActions = new StmList(prepareActions, new Move(new Mem(new Temp(*baseAddress), location),
                new Name(GetTableName(), location), location), location);
        for (auto fieldsOffset: fieldsOffsets) {
            prepareActions = new StmList(prepareActions, new Move(
                    new Binop(Binop::PLUS, new Mem(new Temp(*baseAddress), location),
                              new Const(fieldsOffset.second + wordSize * (1), location), location),
                    new Const(0, location), location), location);
        }
        return new ESeq(prepareActions, new Mem(new Temp(*baseAddress), location), location);
    }

    X86MiniJavaClassStruct::X86MiniJavaClassStruct(const NSymbolTable::ClassInfo &info,
                                                   const NSymbolTable::SymbolTable& symbolTable)
            : className(info.GetId()) {
        std::vector<const NSymbolTable::ClassInfo*> classesStack;
        for (auto classId = info.GetId();
                classId != nullptr; classId = symbolTable.GetClassInfo(classId).GetSuperClassId()) {
            classesStack.push_back(&symbolTable.GetClassInfo(classId));
        }

        for (const auto classInfo : classesStack) {
            for (auto var: classInfo->GetVarsInfo()) {
                const NSymbolTable::VariableInfo &varInfo = var.second;
                int curSize = fieldsOffsets.size();
                fieldsOffsets.insert({varInfo.GetId(), curSize});
            }

            for (auto &method: classInfo->GetMethodsInfo()) {
                const NSymbolTable::MethodInfo &methodInfo = method.second;
                vTableIndices.insert({ methodInfo.GetId(), vtableEntries.size() });
                vtableEntries.push_back(&methodInfo);
            }
        }
    }

    IClassStruct* X86MiniJavaClassStructBuilder::GetClassStruct(const NSymbolTable::ClassInfo& info,
                                                                const NSymbolTable::SymbolTable& symbolTable) const {
        return new X86MiniJavaClassStruct(info, symbolTable);
    }
}
