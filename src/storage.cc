#include "storage.h"
#include <vcruntime_string.h>

namespace {
    const int BASIC_FILE_MONTHS = 2;
    const int BASIC_OBJECT_MONTHS = 3;
    const int YEAR_MONTHS = 12;
}

Storage::Storage(int months, int capacity, StorageType type) :months(months), capacity(capacity), type(type)
{

}

double Storage::charge() const
{
    double price = 0;
    switch (type)
    {
    case ST_BLOCK_STORAGE:
        price += 40;
        if (capacity > BASIC_BLOCK_SIZE)
        {
            double exceed = (double)(capacity) - BASIC_BLOCK_SIZE;
            price += months * exceed * 3;
        }
        break;
    case ST_FILE_STORAGE:
        price += 20;
        if (months > BASIC_FILE_MONTHS)
        {
            double exceed = (double)(months) - BASIC_FILE_MONTHS;
            price += exceed * 1.5;
        }
        break;
    case ST_OBJECT_STORAGE:
        price += 10;
        if (months > BASIC_OBJECT_MONTHS)
        {
            double exceed = (double)(months) - BASIC_OBJECT_MONTHS;
            price += exceed * capacity * 1.5;
        }
        break;
    default:
        break;
    }

    return price;
}

int Storage::levels() const
{
    if (type == ST_OBJECT_STORAGE && months > YEAR_MONTHS)
    {
        return 1;
    }
    return 0;
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
