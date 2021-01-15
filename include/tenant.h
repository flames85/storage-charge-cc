#pragma once

struct Storage;

struct Tenant
{
    Tenant();
    void charge(double* total, int* levels);
    void add(Storage* storage);

private:
    enum { MAX_NUM_STORAGE = 32 };
    int numOfStorages = 0;              /* 租期数目 */
    Storage* stroages[MAX_NUM_STORAGE]; /* 租期列表 */
};