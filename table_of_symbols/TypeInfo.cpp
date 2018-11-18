#include "TypeInfo.h"

#include <cassert>

namespace NSymbolTable {
    TypeInfo::TypeInfo(NSyntaxTree::EType _type, const Symbol *_classId) noexcept : type(_type) {
        if (type == NSyntaxTree::CLASS) {
            assert(_classId != nullptr);
            classId = _classId;
        }
    }

    const Symbol* TypeInfo::GetClassId() const {
        assert(type == NSyntaxTree::CLASS);
        return classId;
    }

    bool TypeInfo::operator==(const TypeInfo &t) const {
        if (type != CLASS)
            return type == t.type;

        return type == t.type && classId == t.classId;
    }

    bool TypeInfo::operator!=(const TypeInfo &t) const {
        return !(*this == t);
    }

    std::string TypeInfo::ToString() const {
        switch (type) {
            case NSyntaxTree::INT:
            {
                return "int";
            }
            case NSyntaxTree::INT_ARRAY:
            {
                return "int[]";
            }
            case NSyntaxTree::BOOL:
            {
                return "boolean";
            }
            case NSyntaxTree::CLASS:
            {
                return classId->String();
            }
            default:
                assert(false);
        }
    }
}
