#include "Location.h"

namespace NTree {
    Position ConvertPosition(const Comp::position &pos) {
        return {pos.line, pos.column};
    }

    Location ConvertLocation(const Comp::location &loc) {
        return {ConvertPosition(loc.begin), ConvertPosition(loc.end)};
    }
}

