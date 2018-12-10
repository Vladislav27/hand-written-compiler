#pragma once

#include "IExp.h"

#include <vector>

namespace NIRTree {
    class Temp : public IExp {
    public:
        enum TempType {
            ID,
            NAME
        };


        const int id;

        const int localId;
        const std::string name;
        TempType type;

        explicit Temp(int localId = 12345, const Location &location = {});
        explicit Temp(const std::string &name, const Location &location = {}, int uniqueId = -1);

        void Accept(IIRVisitor *visitor) const override;

    private:
        static int counter;
        bool unique;
    };

    typedef std::vector<const Temp*> TempList;
}