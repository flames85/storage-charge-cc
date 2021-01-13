#include "storage.h"

void charge(const Tenant* tenant, double* total, int* levels)
{
    int index = 0;
    double price = 0.0;
    double exceed = 0.0;

    for (index = 0; index < tenant->numOfLeases && index < MAX_NUM_LEASE; index++)
    {
        price = 0;

        switch (tenant->leases[index]->storage->type)
        {
        case ST_BLOCK_STORAGE:
            price += 40;
            if (tenant->leases[index]->storage->capacity > BASIC_BLOCK_SIZE)
            {
                exceed = tenant->leases[index]->storage->capacity - BASIC_BLOCK_SIZE;
                price += tenant->leases[index]->months * exceed * 3;
            }
            break;
        case ST_FILE_STORAGE:
            price += 20;
            if (tenant->leases[index]->months > 2)
            {
                exceed = tenant->leases[index]->months - 2;
                price += exceed * 1.5;
            }
            break;
        case ST_OBJECT_STORAGE:
            price += 10;
            if (tenant->leases[index]->months > 3)
            {
                exceed = tenant->leases[index]->months - 3;
                price += exceed * tenant->leases[index]->storage->capacity * 1.5;
            }
            break;
        default:
            break;
        }

        if ((tenant->leases[index]->storage->type == ST_OBJECT_STORAGE)
                && (tenant->leases[index]->months > 12))
        {
            *levels += 1;
        }

        *total += price;
    }
}
