#pragma once

#include "Common.h"

#include "IdentifierInfo.h"

#include <abstr/tree/Type.h>
#include <abstr/StringInterner.h>

namespace NSymbolTable {
    class TypeInfo {
        NTree::EType type;
        const NTree::Symbol *classId;
    public:
        explicit TypeInfo(NTree::EType _type, const NTree::Symbol *_classId = nullptr) noexcept;

        TypeInfo(const NTree::Type &_type) : type(_type.type), classId(_type.id) {
        }

        TypeInfo(const TypeInfo &info) = default;
        TypeInfo &operator=(const TypeInfo &info) = default;

        TypeInfo(TypeInfo &&info) = default;
        TypeInfo &operator=(TypeInfo &&info) = default;

        const NTree::EType& GetType() const { return type; }
        const NTree::Symbol* GetClassId() const;

        bool operator==(const TypeInfo& t) const;
        bool operator!=(const TypeInfo& t) const;

        std::string ToString() const;
    };

    using NTree::INT;
    using NTree::INT_ARRAY;
    using NTree::BOOL;
    using NTree::CLASS;

    const static TypeInfo IntType = TypeInfo(NTree::INT);
    const static TypeInfo IntArrayType = TypeInfo(NTree::INT_ARRAY);
    const static TypeInfo BooleanType = TypeInfo(NTree::BOOL);
}