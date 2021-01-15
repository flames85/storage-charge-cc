#pragma once
#include <set>
struct StorageType;

/**
 * 存储资源
 * */


struct Creator;

struct Storage
{
    enum class Type
    {
        ST_BLOCK_STORAGE,  /* 块存储 */
        ST_FILE_STORAGE,   /* 文件存储 */
        ST_OBJECT_STORAGE, /* 对象存储 */
    };

    

    Storage(int months, int capacity, Type type, const Creator& creator);
    double charge() const;
    int levels() const;

private:
    int months = 0;         /* 租期时长 */
    int capacity = 0;       /* 存储容量，单位: MB */
    StorageType* type;      /* 存储类型 */

};

struct Creator
{
    void regist(Storage::Type);
    StorageType* createStorage(Storage::Type type) const;

    std::set<Storage::Type> m_regs;
};