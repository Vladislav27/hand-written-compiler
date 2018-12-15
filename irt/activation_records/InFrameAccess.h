#pragma once

#include "IAccess.h"

namespace NIRTree {
    class InFrameAccess: public IAccess {
    public:
        InFrameAccess(ERecordsType type, int size, int offset);
        ERecordsType GetRecordType() override {
            return recordType;
        }

        int GetSize() const override {
            return size;
        }

        IExp* GetExp(Temp* fp, const Location& location) const override;

    private:
        const int size;
        const ERecordsType recordType;

        const int offset;
    };
}