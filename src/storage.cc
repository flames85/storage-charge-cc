#include "storage.h"
#include "ObjectStorageType.h"
#include "FileStorageType.h"
#include "BlockStorageType.h"

void Creator::regist(Storage::Type type)
{
    m_regs.insert(type);
}

StorageType* Creator::createStorage(Storage::Type type) const
{
    if (m_regs.find(type) == m_regs.end())
    {
        return nullptr;
    }

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



Storage::Storage(int months, int capacity, Type type, const Creator &creator) :
    months(months), 
    capacity(capacity),
type(creator.createStorage(type))
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

