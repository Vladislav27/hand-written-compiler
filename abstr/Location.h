#pragma once

#include <string>
#include <sstream>
#include <location.hh>

namespace NTree {
    struct Position {
        uint32_t line;
        uint32_t column;

        std::string ToString() const {
            std::stringstream buf;
            buf << "(" << line << ", " << column << ")";
            return buf.str();
        }
    };

    struct Location {
        Position begin;
        Position end;

        std::string ToString() const {
            return begin.ToString() + " - " + end.ToString();
        }
    };

    Position ConvertPosition(const Comp::position& pos);

    Location ConvertLocation(const Comp::location& loc);
}
