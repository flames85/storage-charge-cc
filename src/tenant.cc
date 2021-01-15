#include "tenant.h"
#include <vcruntime_string.h>
#include "storage.h"


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
