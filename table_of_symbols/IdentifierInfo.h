#pragma once

#include "Common.h"

#include "Exceptions.h"

namespace NSymbolTable {
    class IdentifierInfo {
    protected:
        const Symbol* id = nullptr;
        Location location;

    public:
        inline IdentifierInfo(const Symbol* _id, const Location& _location)
            : id(_id), location(_location) {
        }

        inline IdentifierInfo(const IdentifierInfo &info) = default;
        inline IdentifierInfo &operator=(const IdentifierInfo &info) = default;

        inline IdentifierInfo(IdentifierInfo &&info) = default;
        inline IdentifierInfo &operator=(IdentifierInfo &&info) = default;

        inline const Symbol* GetId() const {
            return id;
        }

        inline const Location& GetLocation() const {
            return location;
        }

        virtual ~IdentifierInfo() = default;
    };

    template<class Map>
    void CheckIdentifier(const Map& map, const Symbol *newId, const Location &newLocation) {
        if (map.find(newId) != map.end()) {
            throw RedefinitionException(newLocation, newId, map.at(newId).GetLocation());
        }
    }
}