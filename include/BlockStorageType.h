#pragma once
#include "storageType.h"

struct BlockStorageType : public StorageType
{
    virtual double charge(int capacity, int months) const override
    {
        double price = 40;
        if (capacity > BASIC_BLOCK_SIZE)
        {
            double exceed = (double)(capacity)-BASIC_BLOCK_SIZE;
            price += months * exceed * 3;
        }
        return price;
    }

    virtual ~BlockStorageType() {}
};