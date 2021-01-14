#include "storage.h"
#include <vcruntime_string.h>

namespace {
    const int BASIC_FILE_MONTHS = 2;
    const int BASIC_OBJECT_MONTHS = 3;
    const int YEAR_MONTHS = 12;
}

struct StorageType
{
    virtual ~StorageType() {}

    virtual double charge(int capacity, int months) const = 0;

    virtual int levels(int months) const
    {
        return 0;
    }
};

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


StorageType* createStorage(Storage::Type type)
{
    StorageType* t = nullptr;
    switch (type)
    {
    case Storage::Type::ST_BLOCK_STORAGE:
        t = new BlockStorageType;
        break;
    case Storage::Type::ST_FILE_STORAGE:
        t = new FileStorageType;
        break;
    case Storage::Type::ST_OBJECT_STORAGE:
        t = new ObjectStorageType;
        break;
    default:
        t = nullptr;
        break;
    }
    return t;
}

Storage::Storage(int months, int capacity, Type type) :months(months), capacity(capacity), type(createStorage(type))
{

}

double Storage::charge() const
{
    return type->charge(capacity, months);
}

int Storage::levels() const
{
    return type->levels(months);
}

Tenant::Tenant() {
    memset(stroages, 0x0, sizeof(stroages));
}

void Tenant::add(Storage* storage)
{
    stroages[numOfStorages++] = storage;
}
void Tenant::charge(double* total, int* levels)
{
    for (int index = 0; index < numOfStorages && index < MAX_NUM_STORAGE; index++)
    {
        const Storage* storage = stroages[index];
        *levels += storage->levels();
        *total += storage->charge();
    }
}
