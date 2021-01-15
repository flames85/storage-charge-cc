#pragma once
#include "storageType.h"

struct NullStorageType : public StorageType
{
    virtual double charge(int capacity, int months) const override
    {
        return -1;
    }

    virtual int levels(int months) const override
    {
        return -1;
    }

    virtual ~NullStorageType() {}
};
