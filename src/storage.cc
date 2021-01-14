#include "storage.h"
#include <vcruntime_string.h>

namespace {
    const int BASIC_FILE_MONTHS = 2;
    const int BASIC_OBJECT_MONTHS = 3;
    const int YEAR_MONTHS = 12;
}

Lease::Lease(int months, Storage* storage):months(months), storage(storage)
{

}

double Lease::charge() const
{
    double price = 0;
    switch (storage->type)
    {
    case ST_BLOCK_STORAGE:
        price += 40;
        if (storage->capacity > BASIC_BLOCK_SIZE)
        {
            double exceed = (double)(storage->capacity) - BASIC_BLOCK_SIZE;
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
            price += exceed * storage->capacity * 1.5;
        }
        break;
    default:
        break;
    }

    return price;
}

int Lease::levels() const
{
    if ((storage->type == ST_OBJECT_STORAGE)
        && (months > YEAR_MONTHS))
    {
        return 1;
    }
    return 0;
}

Tenant::Tenant() {
    memset(leases, 0x0, sizeof(leases));
}

void Tenant::add(Lease* lease)
{
    leases[numOfLeases++] = lease;
}
void Tenant::charge(double* total, int* levels)
{
    for (int index = 0; index < numOfLeases && index < MAX_NUM_LEASE; index++)
    {
        const Lease* lease = leases[index];
        *levels += lease->levels();
        *total += lease->charge();
    }
}
