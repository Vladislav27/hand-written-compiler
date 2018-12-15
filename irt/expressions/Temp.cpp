#include "Temp.h"

#include <abstr/Location.h>

namespace NIRTree {
    Temp::Temp(int localId, const Location &location)
        : IExp(location), id(counter++), localId(localId), name(""), type(ID), unique(false) {
    }

    Temp::Temp(const std::string &name, const Location &location, int uniqueId)
        : IExp(location), id(counter++), localId(-1), name(name), type(NAME), unique(uniqueId != -1) {
    }

    int Temp::counter = 0;
}
