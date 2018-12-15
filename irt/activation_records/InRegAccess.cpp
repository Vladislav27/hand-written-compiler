#include "InRegAccess.h"

#include <irt/NodeTypes.h>

namespace NIRTree {
    const char* const ArPrefix = "AR::";

    IExp *InRegAccess::GetExp(NIRTree::Temp *fp, const NTree::Location &location) const {
        delete fp;
        return new Mem(new Temp(*temp), location);
    }

    InRegAccess::InRegAccess(IAccess::ERecordsType _type, int _size, const std::string &name)
            : recordType(_type), size(_size), name(name), id(-1), temp(new Temp(ArPrefix + name)) {
    }

    InRegAccess::InRegAccess(IAccess::ERecordsType _type, int _size, int id)
            : recordType(_type), size(_size), name(""), id(id), temp(new Temp(id)) {
    }

    InRegAccess::InRegAccess(const InRegAccess& other):
            recordType(other.recordType),
            size(other.size),
            name(other.name),
            id(other.id),
            temp(new Temp(*other.temp.get())) {
    }
}
