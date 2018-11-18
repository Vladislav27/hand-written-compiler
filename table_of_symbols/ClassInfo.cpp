#include "ClassInfo.h"

namespace NSymbolTable {
    ClassInfo::ClassInfo(const Symbol* _classId, const NSyntaxTree::Location& _location, const Symbol* _superClassId)
        : IdentifierInfo(_classId, _location), superClassId(_superClassId) {
    }

    void ClassInfo::InsertVarInfo(const VariableInfo& varInfo) {
        membersInfo.insert({varInfo.GetId(), varInfo});
    }

    void ClassInfo::InsertMethodInfo(const MethodInfo& methodInfo) {
        methodsInfo.insert({methodInfo.GetId(), methodInfo});
    }

    bool ClassInfo::HasMember(const Symbol *id) const {
        return membersInfo.find(id) != membersInfo.end();
    }

    bool ClassInfo::HasMethod(const Symbol *id) const {
        return methodsInfo.find(id) != methodsInfo.end();
    }

    TypeInfo ClassInfo::GetType() const {
        return TypeInfo(CLASS, id);
    }
}