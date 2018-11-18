#include "TypeInfo.h"

#include <cassert>

namespace NSymbolTable {
    TypeInfo::TypeInfo(NTree::EType _type, const Symbol *_classId) noexcept : type(_type) {
        if (type == NTree::CLASS) {
            assert(_classId != nullptr);
            classId = _classId;
        }
    }

    const Symbol* TypeInfo::GetClassId() const {
        assert(type == NTree::CLASS);
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
            case NTree::INT:
            {
                return "int";
            }
            case NTree::INT_ARRAY:
            {
                return "int[]";
            }
            case NTree::BOOL:
            {
                return "boolean";
            }
            case NTree::CLASS:
            {
                return classId->String();
            }
            default:
                assert(false);
        }
    }
}
