#pragma once
#include "storageType.h"

struct ObjectStorageType : public StorageType
{
    virtual double charge(int capacity, int months) const override
    {
        double price = 10;
        if (months > BASIC_OBJECT_MONTHS)
        {
            double exceed = (double)(months)-BASIC_OBJECT_MONTHS;
            price += exceed * capacity * 1.5;
        }
        return price;
    }

    virtual int levels(int months) const override
    {
        return months > YEAR_MONTHS ? 1 : 0;
    }

    virtual ~ObjectStorageType() {}
};
