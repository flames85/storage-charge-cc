#pragma once
struct StorageType
{
    virtual ~StorageType() {}

    virtual double charge(int capacity, int months) const = 0;

    virtual int levels(int months) const
    {
        return 0;
    }

    const int BASIC_FILE_MONTHS = 2;
    const int BASIC_OBJECT_MONTHS = 3;
    const int YEAR_MONTHS = 12;
    const int BASIC_BLOCK_SIZE = 1024; 
};
