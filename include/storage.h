#ifndef HCE627815_E322_4865_8463_CAA81513C14F
#define HCE627815_E322_4865_8463_CAA81513C14F

#define BASIC_BLOCK_SIZE 1024 /* 块存储的最大值 */
#define MAX_NUM_STORAGE  32   /* 每个租户的最大资源租期数 */


struct StorageType;

/**
 * 存储资源
 * */
struct Storage
{
    enum class Type
    {
        ST_BLOCK_STORAGE,  /* 块存储 */
        ST_FILE_STORAGE,   /* 文件存储 */
        ST_OBJECT_STORAGE, /* 对象存储 */
    } ;
    Storage(int months, int capacity, Type type);
    double charge() const;
    int levels() const;

private:
    int months = 0;         /* 租期时长 */
    int capacity = 0;       /* 存储容量，单位: MB */
    StorageType* type;      /* 存储类型 */
};

/**
 * 租户
 * */
struct Tenant
{
    Tenant();
    void charge(double* total, int* levels);
    void add(Storage* storage);

private:
    int numOfStorages = 0;              /* 租期数目 */
    Storage* stroages[MAX_NUM_STORAGE]; /* 租期列表 */
} ;

#endif
