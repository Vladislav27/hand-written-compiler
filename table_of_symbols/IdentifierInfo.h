#pragma once

#include "Common.h"

#include "Exceptions.h"

namespace NSymbolTable {
    class IdentifierInfo {
    protected:
        const  NTree::Symbol* id;
        NTree::Location location;

    public:
        IdentifierInfo(const  NTree::Symbol* _id, const  NTree::Location& _location)
            : id(_id), location(_location) {
        }

        IdentifierInfo(const IdentifierInfo &info) = default;
        IdentifierInfo &operator=(const IdentifierInfo &info) = default;

        IdentifierInfo(IdentifierInfo &&info) = default;
        IdentifierInfo &operator=(IdentifierInfo &&info) = default;

        const  NTree::Symbol* GetId() const {
            return id;
        }

        const  NTree::Location& GetLocation() const {
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