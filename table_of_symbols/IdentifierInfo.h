#pragma once

#include "Common.h"

#include "Exceptions.h"

namespace NSymbolTable {
    class IdentifierInfo {
    protected:
        const  NTree::Symbol* id = nullptr;
        NTree::Location location;

    public:
        inline IdentifierInfo(const  NTree::Symbol* _id, const  NTree::Location& _location)
            : id(_id), location(_location) {
        }

        inline IdentifierInfo(const IdentifierInfo &info) = default;
        inline IdentifierInfo &operator=(const IdentifierInfo &info) = default;

        inline IdentifierInfo(IdentifierInfo &&info) = default;
        inline IdentifierInfo &operator=(IdentifierInfo &&info) = default;

        inline const  NTree::Symbol* GetId() const {
            return id;
        }

        inline const  NTree::Location& GetLocation() const {
            return location;
        }

        virtual ~IdentifierInfo() = default;
    };

    template<class Map>
    void CheckIdentifier(const Map& map, const  NTree::Symbol *newId, const  NTree::Location &newLocation) {
        if (map.find(newId) != map.end()) {
            throw RedefinitionException(newLocation, newId, map.at(newId).GetLocation());
        }
    }
}