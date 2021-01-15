#pragma once
#include "storageType.h"

struct FileStorageType : public StorageType
{
    virtual double charge(int capacity, int months) const override
    {
        double price = 20;
        if (months > BASIC_FILE_MONTHS)
        {
            double exceed = (double)(months)-BASIC_FILE_MONTHS;
            price += exceed * 1.5;
        }
        return price;
    }

    virtual ~FileStorageType() {}
};