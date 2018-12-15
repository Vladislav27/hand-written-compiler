#pragma once

#include "IAccess.h"


namespace NIRTree {
    class InRegAccess: public IAccess {
    public:
        InRegAccess(ERecordsType _type, int _size, const std::string& name);
        InRegAccess(ERecordsType _type, int _size, int id);
        InRegAccess(const InRegAccess& other);

        ERecordsType GetRecordType() override {
            return recordType;
        }

        int GetSize() const override {
            return size;
        }

        IExp* GetExp(Temp* fp, const Location& location) const override;

    private:
        const ERecordsType recordType;
        const int size;
        const std::string name;
        int id;
        std::unique_ptr<Temp> temp;
    };
}